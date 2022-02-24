#version 330 core

uniform vec2 u_resolution;
uniform float radius_x;
uniform float radius_y;

float sdSegment(vec2 p, vec2 a, vec2 b )
{
    vec2 pa = p-a, ba = b-a;
    float h = clamp( dot(pa,ba)/dot(ba,ba), 0.0, 1.0 );
    return length( pa - ba*h );
}

float sd_Circle(vec2 p, float r)
{
	return length(p) - r;
}

vec3 sdCircle_outline(vec2 p, float r, float thickness)
{
	float dist = sd_Circle(p, r);
	vec3 colour = 1.0 - vec3(smoothstep(0.0, 1.0, dist));

	colour = mix(colour, vec3(0.0, 0.2, 0.33) / vec3(6), smoothstep(thickness, thickness * 2, abs(dist)));

	return colour;
}

float sdArc(vec2 p, vec2 sc, float ra, float rb )
{
    p.x = abs(p.x);
    return ((sc.y*p.x>sc.x*p.y) ? length(p-sc*ra) : abs(length(p)-ra)) - rb;
}

float sdBox(vec2 p, vec2 b )
{
    vec2 d = abs(p)-b;
    return length(max(d,0.0)) + min(max(d.x,d.y),0.0);
}

float sdEquilateralTriangle(  in vec2 p, in float r )
{
    const float k = sqrt(3.0);
    p.x = abs(p.x) - r;
    p.y = p.y + r/k;
    if( p.x+k*p.y>0.0 ) p=vec2(p.x-k*p.y,-k*p.x-p.y)/2.0;		
    p.x -= clamp( p.x, -2.0*r, 0.0 );
    return -length(p)*sign(p.y);
}

void main()
{
	vec2 res = vec2(2000, 1000);
	vec2 std =  ( (2.0 * gl_FragCoord.xy - res.xy) / res.y ) * 2.0;
	vec3 colour = vec3(0.0);
	vec3 colour_2 = vec3(0.0);
	
	//vec2 sc = vec2(sin(3.14 * radius +0.5), cos(3.14 * radius + 0.5));
	//float arc_dist = sdArc(std + 0.3, sc, 0.2, 0.001);
	//colour = 1.0 - sin(arc_dist) * 200 * vec3(1.0);

	colour_2 = sdCircle_outline(std + vec2(radius_x, radius_y), 0.5, 0.002);
	colour = sdCircle_outline(std + vec2(radius_x, radius_y), 0.1, 0.001);
	
	float dist_segment = sdSegment(std + vec2(radius_x, radius_y), vec2(1.0), vec2(-1.0)) - 0.002;
	float dist_segment_2 = sdSegment(std + vec2(radius_x, radius_y), vec2(-1.0, 1.0), vec2(1.0, -1.0)) - 0.002;
	
	vec3 colour_4 = (dist_segment_2 >0.0) ? vec3(0.0, 0.2, 0.33) / vec3(3) : vec3(1.0, 1.0, 1.0);
	vec3 colour_3 = (dist_segment >0.0) ? vec3(0.0, 0.2, 0.33) / vec3(6) : vec3(1.0, 1.0, 1.0);

	colour_2 = ( colour_2 + colour + colour_3 + colour_4);

	gl_FragColor = vec4(colour_2, 1.0);
}