#version 330 core

in vec2 pos; // range [0,1]x[0,1]

uniform sampler1D data0;
uniform sampler1D data1;
uniform int n0;
uniform int n1;
uniform vec3 backgroundcolor;
uniform float linewidth0;
uniform float linewidth1;
uniform vec3 linecolor0;
uniform vec3 linecolor1;
uniform float markersize0;
uniform float markersize1;
uniform vec3 markercolor0;
uniform vec3 markercolor1;
uniform bool showActive;
uniform vec2 activePosition;
uniform float activeMarkerSize;
uniform vec3 activecolor;

// Output frag color
out vec4 fragColor;

float DistanceToLineSegment(vec2 p, vec2 a, vec2 b)
{
    vec2 pa = p - a, ba = b - a;
    float h = clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);
    return length(pa - ba * h);
}

void main(void)
{

    fragColor = vec4(backgroundcolor, 1.0f);

    vec2 P; // will be assigned by reading texture data
    vec2 P_next;

    // Draw line0
    float dist0 = 1000.f; // dist to data0
    for (int i = 0; i < n0 - 1; i++)
    {
        float i_float = float(i);
        P = texture(data0, (i_float + 0.5) / n0).xy;
        P_next = texture(data0, (i_float + 1 + 0.5) / n0).xy;
        dist0 = min(dist0, DistanceToLineSegment(pos, P, P_next));
    }
    if (dist0 < 0.5 * linewidth0)
    {
        fragColor = vec4(linecolor0, 1.0f);
    }
    // Draw marker0
    for (int i = 0; i < n0; i++)
    {
        float i_float = float(i);
        P = texture(data0, (i_float + 0.5) / n0).xy;
        if (length(pos - P) < 0.5 * markersize0)
        {
            fragColor = vec4(markercolor0, 1.0f);
        }
    }

    // Draw line1
    float dist1 = 1000.f; // dist to data1
    for (int i = 0; i < n1 - 1; i++)
    {
        float i_float = float(i);
        P = texture(data1, (i_float + 0.5) / n1).xy;
        P_next = texture(data1, (i_float + 1 + 0.5) / n1).xy;
        dist1 = min(dist1, DistanceToLineSegment(pos, P, P_next));
    }
    if (dist1 < 0.5 * linewidth1)
    {
        fragColor = vec4(linecolor1, 1.0f);
    }
    // Draw marker1
    for (int i = 0; i < n1; i++)
    {
        float i_float = float(i);
        P = texture(data1, (i_float + 0.5) / n1).xy;
        if (length(pos - P) < 0.5 * markersize1)
        {
            fragColor = vec4(markercolor1, 1.0f);
        }
    }

    if (showActive && length(pos - activePosition) < 0.5 * activeMarkerSize)
    {
        fragColor = vec4(activecolor, 1.0f);
    }
}
