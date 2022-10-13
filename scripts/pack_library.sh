#!/bin/bash

ar -M <<EOM
	CREATE libikura.a
	ADDLIB ./src/engine/libappEngine.a
	ADDLIB ./src/engine/librenderEngine.a
	ADDLIB ./src/misc/libinitVulkanHppDispatchLoader.a
	ADDLIB ./src/renderComponent/librenderComponent.a
	ADDLIB ./src/shape/libshape.a
	ADDLIB ./src/window/libwindow.a
	ADDLIB ./src/window/libvirtualWindow.a
	ADDLIB ./src/window/libnativeWindow.a
	ADDLIB ./libikura-ext-lib.a
	SAVE
	END
EOM
