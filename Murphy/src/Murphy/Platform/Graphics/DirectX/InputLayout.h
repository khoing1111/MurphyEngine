#pragma once

#include "Bindable.h"
#include "Exceptions.h"
#include "Shaders.h"

namespace Murphy::DirectX
{
    class InputLayout : public Bindable
    {
    public:
        InputLayout(Renderer& renderer, const D3D11_INPUT_ELEMENT_DESC* inputElemDesc, const UINT inputElemDescSize, VertexShader& vertexShader)
        {
            HRESULT hr;
            if (FAILED(hr = renderer.GetDevice()->CreateInputLayout(
                inputElemDesc, inputElemDescSize,
                vertexShader.GetBlob()->GetBufferPointer(), vertexShader.GetBlob()->GetBufferSize(),
                m_InputLayout.GetAddressOf()
            )))
                throw UnableToCreateInputLayout(hr);
        }

        virtual void Bind(Renderer& renderer) override
        {
            renderer.GetDeviceContext()->IASetInputLayout(m_InputLayout.Get());
        }

    private:
        MP_COMPTR<ID3D11InputLayout> m_InputLayout;
    };
}