#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;

struct Camera {
	vec3 pos;
	vec3 front;
	vec3 up;
	vec3 right;
	// degree
	float fov;
	float near;
	// weight / height
	float ratio;
};

struct Sphere {
	vec3 pos;
	float r;
};

struct DirLight {
	vec3 dir;
	vec3 color;
	vec3 ambient;
};

uniform Camera cam;
uniform Sphere sph;
uniform DirLight lit;

float IntersectSph(vec3 ro, vec3 rd, Sphere s) {
	float A = dot(rd, rd);
	float B = 2 * dot(rd, ro - s.pos);
	float C = dot(ro - s.pos, ro - s.pos) - s.r * s.r;
	float delta = B * B - 4 * A * C;
	if (delta <= 0.)
		return -1.;

	float t1 = (-B - sqrt(B * B - 4 * A * C)) / (2 * A);
	float t2 = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);
	// both <= 0
	if (t1 <= 0 && t2 <= 0)
		return -1.;
	// both > 0
	if (t1 > 0)
		return t1;
	// t1 <= 0, t2 > 0, the ray origin is in the sphere
	return -1.;
}

void main()
{
	// generate ray according to the FragPos
	vec3 screen_center = cam.pos + normalize(cam.front) * cam.near;
	vec3 screen_up_dir = normalize(cam.up);
	vec3 screen_right_dir = normalize(cam.right);
	float height = cam.near * tan(radians(cam.fov / 2)) * 2;
	float width = height * cam.ratio;
	vec3 ray_origin = screen_center + screen_right_dir * width * FragPos.x / 2
					+ screen_up_dir * height * FragPos.y / 2;
	
	vec3 ray_dir = normalize(ray_origin - cam.pos);
	
	// intersect with the scene
	float t = IntersectSph(ray_origin, ray_dir, sph);
	if (t <= 0) {
		FragColor = vec4(0.f, 0.f, 0.f, 1.f);
		return;
	}
	
	vec3 pos = ray_origin + t * ray_dir;
	vec3 normal = normalize(pos - sph.pos);
	float diff = max(dot(normal, normalize(-lit.dir)), 0);
	vec3 color = diff * lit.color * 0.7 + lit.ambient * 0.3;
	FragColor = vec4(color, 1.f);

}