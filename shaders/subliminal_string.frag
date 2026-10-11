#version 460
#include "common.glsl"

// Draw2D_ShSubliminalString (the photo pieces' and the final loop's handwriting): 0.1 x colour at the texture's alpha times
// the string's envelope, drawn with the Draw2D blend mode 2 (render state 0x1B, additive) into the screen buffer the lens
// flares go to, so it is added to the scene before the tonemap curve and the colour LUT (rendering.md 9): a faint, graded
// hand over the scene rather than an opaque grey one on top of everything

layout(push_constant) uniform PassPush {
    uvec4 ids;   // texture index
    vec4 f0;     // string position (materials[1].xy), envelope value, the frame's width in 16:9 frames
    vec4 f1;
    vec4 f2;
    mat4 m;
} pass;

layout(location = 0) in vec2 in_uv;
layout(location = 0) out vec4 out_color;

void main() {
    // the original's quad spans its 16:9 frame; a wider window shows more of the same texels beside it
    float across = pass.f0.w > 0.0 ? pass.f0.w : 1.0;
    vec2 uv = vec2((in_uv.x - 0.5) * across + 0.5, in_uv.y);
    float a = texture(textures[nonuniformEXT(pass.ids.x & 0x3FFFFFFFu)], pass.f0.xy + uv).a;
    float alpha = clamp(pass.f0.z * a, 0.0, 1.0);
    out_color = vec4(vec3(0.1 * alpha), 0.0);
}
