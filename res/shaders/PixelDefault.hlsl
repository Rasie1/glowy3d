struct PixelShaderInput
{
    float4 color : COLOR;
};
 
float4 PixelDefault( PixelShaderInput IN ) : SV_TARGET
{
    return IN.color;
}