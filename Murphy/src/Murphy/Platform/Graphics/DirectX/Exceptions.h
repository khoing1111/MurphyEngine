#pragma once

#include "Murphy/Platform/Windows/Exceptions.h"

namespace Murphy::DirectX
{
    class DirectXRendererRequired : public std::exception
    {
    public:
        DirectXRendererRequired()
            : std::exception("Require DirectX Renderer")
        {
        }
    };

    class UnableToCreateVertexBuffer : public Murphy::Windows::HRESULTException
    {
    public:
        UnableToCreateVertexBuffer(HRESULT& hr) 
            : Murphy::Windows::HRESULTException(std::string("Unable to create vertex buffer"), hr)
        {
        }
    };

    class UnableToCreateIndexBuffer : public Murphy::Windows::HRESULTException
    {
    public:
        UnableToCreateIndexBuffer(HRESULT& hr)
            : Murphy::Windows::HRESULTException(std::string("Unable to create index buffer"), hr)
        {
        }
    };

    class UnableToCreateInputLayout : public Murphy::Windows::HRESULTException
    {
    public:
        UnableToCreateInputLayout(HRESULT& hr)
            : Murphy::Windows::HRESULTException(std::string("Unable to create input layout"), hr)
        {
        }
    };

    class UnableToReadCSOFile : public Murphy::Windows::HRESULTException
    {
    public:
        UnableToReadCSOFile(HRESULT& hr)
            : Murphy::Windows::HRESULTException(std::string("Unable to read cso file"), hr)
        {
        }
    };

    class UnableToCreateVSShader : public Murphy::Windows::HRESULTException
    {
    public:
        UnableToCreateVSShader(HRESULT& hr)
            : Murphy::Windows::HRESULTException(std::string("Unable to create Vertex Shader"), hr)
        {
        }
    };

    class UnableToCreatePSShader : public Murphy::Windows::HRESULTException
    {
    public:
        UnableToCreatePSShader(HRESULT& hr)
            : Murphy::Windows::HRESULTException(std::string("Unable to create Pixel Shader"), hr)
        {
        }
    };
}