#include "Simplex.h"

Simplex& Simplex::operator=(std::initializer_list <glm::vec3> list)
{
	for (auto v = list.begin(); v != list.end(); ++v)
	{
		points[std::distance(list.begin(), v)] = *v;
	}

	dim = list.size();

	return *this;
}

void Simplex::Push(glm::vec3 pnt)
{
	points = { pnt, points[0], points[1], points[2] };
	dim = std::min(dim + 1, 4u);
}