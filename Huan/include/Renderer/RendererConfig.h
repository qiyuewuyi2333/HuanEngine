#pragma once

#ifdef HUAN_USING_OPENGL
    #include "Platform/OpenGL/OpenGLContext.h"
    #include "Platform/OpenGL/Buffer/OpenGLIndexBuffer.h"
    #include "Platform/OpenGL/Buffer/OpenGLVertexBuffer.h"
    #include "Platform/OpenGL/OpenGLVertexArray.h"
    #include "Platform/OpenGL/OpenGLRendererAPI.h"
    // #include "OpenGLBuffer.h"
    using CurrentVertexBuffer =  Huan::OpenGLVertexBuffer;
    using CurrentIndexBuffer  =  Huan::OpenGLIndexBuffer;
    using CurrentVertexArray  =  Huan::OpenGLVertexArray;
    using CurrentRendererAPI  =  Huan::OpenGLRendererAPI;
#elif defined(HUAN_USING_VULKAN)
    // #include "VulkanBuffer.h"
    // typedef VulkanBuffer CurrentBuffer;
#else
    #error "No rendering API selected"
#endif