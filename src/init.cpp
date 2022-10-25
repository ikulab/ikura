#include "init.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

#include <easylogging++.h>
#include <libshaderc_util/io_shaderc.h>
#include <shaderc/shaderc.hpp>

#include "./common/resourceDirectory.hpp"
#include "./misc/shaderCodes.hpp"

namespace ikura {
void compileGlslCodeAndOutput(shaderc::Compiler &compiler,
                              std::filesystem::path outputPath,
                              const char *code, size_t codeSize,
                              shaderc_shader_kind kind, const char *name) {
    // compile ----------
    auto compilationResult =
        compiler.CompileGlslToSpv(code, codeSize, kind, "vertex_shader");

    // error check
    if (compilationResult.GetCompilationStatus() !=
        shaderc_compilation_status_success) {
        std::string msg;
        msg += "Failed to compile shader code.\n";
        msg += compilationResult.GetErrorMessage();
        throw std::runtime_error(msg);
    }

    shaderc_util::string_piece compilationOutput(
        reinterpret_cast<const char *>(compilationResult.cbegin()),
        reinterpret_cast<const char *>(compilationResult.cend()));

    // output ----------
    // prepare stream
    std::ofstream potentialOutputStream;
    auto outputStream = shaderc_util::GetOutputStream(
        outputPath.c_str(), &potentialOutputStream, &std::cerr);

    // error check
    if (!outputStream || outputStream->fail()) {
        throw std::runtime_error("Failed to open shader output stream "
                                 "(provided by libshaderc_util).");
    }

    outputStream->write(compilationOutput.data(), compilationOutput.size());
}

void createDirectoryIfNotExists(std::filesystem::path directoryPath) {
    if (!std::filesystem::exists(directoryPath)) {
        VLOG(VLOG_LV_3_PROCESS_TRACKING)
            << directoryPath << " is not exists. Creating directory...";

        std::filesystem::create_directory(directoryPath);
    }
}

void init() {
    VLOG(VLOG_LV_3_PROCESS_TRACKING) << "Initializing ikura...";

    // create resource directories if not exists
    createDirectoryIfNotExists(createResourceDirectoryPath(""));
    createDirectoryIfNotExists(createResourceDirectoryPath("shaders"));

    // generate .spv files if not exists ----------
    VLOG(VLOG_LV_3_PROCESS_TRACKING) << "Checking for shaders...";
    auto shaderDir = createResourceDirectoryPath("shaders");
    shaderc::Compiler spvCompiler;

    if (!std::filesystem::exists(shaderDir / "vert.spv")) {
        VLOG(VLOG_LV_3_PROCESS_TRACKING)
            << shaderDir / "vert.spv"
            << " is not exists. Generating shader file...";

        // clang-format off
        compileGlslCodeAndOutput(
            spvCompiler,                /* compiler */
            shaderDir / "vert.spv",     /* output path */
            VERTEX_SHADER_CODE.c_str(), /* shader code */
            VERTEX_SHADER_CODE.size(),  /* shader code size */
            shaderc_shader_kind::shaderc_vertex_shader, /* kind */
            "vertex_shader"             /* shader name */
        );
        // clang-format on
    }

    if (!std::filesystem::exists(shaderDir / "frag.spv")) {
        VLOG(VLOG_LV_3_PROCESS_TRACKING)
            << shaderDir / "frag.spv"
            << " is not exists. Generating shader file...";

        // clang-format off
        compileGlslCodeAndOutput(
            spvCompiler,                                  /* compiler */
            shaderDir / "frag.spv",                       /* output path */
            FRAGMENT_SHADER_CODE.c_str(),                 /* shader code */
            FRAGMENT_SHADER_CODE.size(),                  /* shader code size */
            shaderc_shader_kind::shaderc_fragment_shader, /* kind */
            "fragment_shader"                             /* shader name */
        );
        // clang-format on
    }

    VLOG(VLOG_LV_3_PROCESS_TRACKING) << "ikura has been initialized.";
}
} // namespace ikura