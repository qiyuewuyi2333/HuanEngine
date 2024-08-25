#pragma once

#ifdef HUAN_USING_OPENGL
    #include "Platform/OpenGL/OpenGLContext.h"
    #include "Platform/OpenGL/Buffer/OpenGLIndexBuffer.h"
    #include "Platform/OpenGL/Buffer/OpenGLVertexBuffer.h"
    #include "Platform/OpenGL/OpenGLVertexArray.h"
    #include "Platform/OpenGL/OpenGLRendererAPI.h"
    #include "Platform/OpenGL/OpenGLShader.h"
    #include "Platform/OpenGL/Texture/OpenGLTexture2D.h"
    #include "Platform/OpenGL/Material/OpenGLMaterial.h"
    // #include "OpenGLBuffer.h"
    namespace Huan {
        using CurrentVertexBuffer =  OpenGLVertexBuffer;
        using CurrentIndexBuffer  =  OpenGLIndexBuffer;
        using CurrentVertexArray  =  OpenGLVertexArray;
        using CurrentRendererAPI  =  OpenGLRendererAPI;
        using CurrentShader       =  OpenGLShader;
        using CurrentTexture2D    =  OpenGLTexture2D;
        using CurrentMaterial     =  OpenGLMaterial;
    }
#elif defined(HUAN_USING_VULKAN)
    // #include "VulkanBuffer.h"
    // typedef VulkanBuffer CurrentBuffer;
#else
    #error "No rendering API selected"
#endif