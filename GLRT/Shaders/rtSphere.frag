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

uniform Camera cam;
uniform Sphere sph;

float IntersectSph(vec3 ro, vec3 rd, Sphere s) {
	vec3 ray_2_sphere = ro - s.pos;
	float a = dot(rd, rd);
	float b = 2.0 * dot(ray_2_sphere, rd);
	float c = dot(ray_2_sphere, ray_2_sphere) - (s.r * s.r);
	float discriminant = b * b - 4.0 * a * c;
	if (discriminant <= 0)
		return -1.f;
	// two intersect point
    float t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    float t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	// closer one
    return min(t1, t2);
}

float IntersectPlaneZ(vec3 ro, vec3 rd, float z) {
	if ((ro.z - z) * rd.z < 0)
		return 1.f;
	else
		return -1.f;
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

	// intersect with the scene, 
	// suppose the sphere is at the center of the world
	// light is a point light
	//float t = IntersectSph(ray_origin, ray_dir, sph);
	float t = IntersectPlaneZ(ray_origin, ray_dir, 0.f);
	vec3 pos = ray_origin + t * ray_dir;

	// just test
	if (t >= 0.f)
		FragColor = vec4(1.f, 1.f, 1.f, 1.f);
	else
		FragColor = vec4(0.2f, 0.4f, 0.1f, 1.f);
}