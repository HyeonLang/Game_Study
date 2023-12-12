#pragma once
class RectUV : public Shape
{
private:
    D3D11_PRIMITIVE_TOPOLOGY type;

public:
    RectUV(Float2 pos, Float2 size,
        D3D11_PRIMITIVE_TOPOLOGY t = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    ~RectUV();

    D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }
    void Render();
    void Render(ID3D11ShaderResourceView** srv,
        ID3D11SamplerState** sampler_state);

};