#include "RenderableBall.h"

#include <glm/glm.hpp>
#include <glm/gtx/polar_coordinates.hpp>
#include <glm/ext/scalar_constants.hpp>

#include <cstdio>

namespace {
    std::vector<glm::vec3> start_points = {
        glm::vec3(1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f),

        glm::vec3(-1.0f,  1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f),

        glm::vec3(-1.0f,  -1.0f, 1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f)
    };

    std::vector<glm::vec3> end_points = {
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f),

        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, -1.0f, 1.0f),

        glm::vec3(1.0f, 1.0f,  1.0f),
        glm::vec3(1.0f, 1.0f, -1.0f)
    };

    void addIndices(std::vector<TriangleIndices>& indices, const int points_per_eddge, const int start)
    {
        for (int i = 0; i < points_per_eddge - 1; i++) {
            for (int j = 0; j < points_per_eddge - 1; j++) {
                int one = start + points_per_eddge * j + i;
                int two = start + points_per_eddge * j + i + 1;
                int three = start + points_per_eddge * (j + 1) + i;
                int four = start + points_per_eddge * (j + 1) + i + 1;

                indices.push_back(TriangleIndices{ glm::ivec3(one, two, three) });
                indices.push_back(TriangleIndices{ glm::ivec3(two, three, four) });
            }
        }
    }
    
}


std::tuple<std::vector<PositionNormalVertex>, std::vector<TriangleIndices>> BallData::buildBallVertices2(int midpoints)
{
    std::vector<PositionNormalVertex> vertices;
    std::vector<TriangleIndices> indices;

    const int subdivision = glm::pow(midpoints, 2) + 1;

    for (int face = 0; face < 1; face++) {
        auto start = glm::normalize(start_points[0]);
        auto end = glm::normalize(end_points[0]);

        const auto dd = (end - start) / ((float)subdivision - 1.0f);

        for (int i = 0; i < subdivision; i++) {
            for (int j = 0; j < subdivision; j++) {
                glm::vec3 mid = start + dd * glm::vec3(0.0f,i,j);

                glm::vec3 v = glm::normalize(mid);//toEuclid(mid);

                vertices.push_back(PositionNormalVertex{ v, v });

            }
        }
    }

    addIndices(indices, subdivision, 0);

    for (int face = 0; face < 1; face++) {
        auto start = glm::normalize(start_points[1]);
        auto end = glm::normalize(end_points[1]);

        const auto dd = (end - start) / ((float)subdivision - 1.0f);

        for (int i = 0; i < subdivision; i++) {
            for (int j = 0; j < subdivision; j++) {
                glm::vec3 mid = start + dd * glm::vec3(0.0f,i, j);

                glm::vec3 v = glm::normalize(mid);//toEuclid(mid);

                vertices.push_back(PositionNormalVertex{ v, v });

            }
        }
    }

    int size = subdivision * subdivision;

    addIndices(indices, subdivision, size);

    for (int face = 0; face < 1; face++) {
        auto start = glm::normalize(start_points[2]);
        auto end = glm::normalize(end_points[2]);

        const auto dd = (end - start) / ((float)subdivision - 1.0f);

        for (int i = 0; i < subdivision; i++) {
            for (int j = 0; j < subdivision; j++) {
                glm::vec3 mid = start + dd * glm::vec3(i, 0.0f, j);

                glm::vec3 v = glm::normalize(mid);//toEuclid(mid);

                vertices.push_back(PositionNormalVertex{ v, v });

            }
        }
    }

    size += subdivision * subdivision;

    addIndices(indices, subdivision, size);

    for (int face = 0; face < 1; face++) {
        auto start = glm::normalize(start_points[3]);
        auto end = glm::normalize(end_points[3]);

        const auto dd = (end - start) / ((float)subdivision - 1.0f);

        for (int i = 0; i < subdivision; i++) {
            for (int j = 0; j < subdivision; j++) {
                glm::vec3 mid = start + dd * glm::vec3(i, 0.0f, j);

                glm::vec3 v = glm::normalize(mid);//toEuclid(mid);

                vertices.push_back(PositionNormalVertex{ v, v });

            }
        }
    }

    size += subdivision * subdivision;

    addIndices(indices, subdivision, size);

    for (int face = 0; face < 1; face++) {
        auto start = glm::normalize(start_points[4]);
        auto end = glm::normalize(end_points[4]);

        const auto dd = (end - start) / ((float)subdivision - 1.0f);

        for (int i = 0; i < subdivision; i++) {
            for (int j = 0; j < subdivision; j++) {
                glm::vec3 mid = start + dd * glm::vec3(i, j,0.0f);

                glm::vec3 v = glm::normalize(mid);//toEuclid(mid);

                vertices.push_back(PositionNormalVertex{ v, v });

            }
        }
    }

    size += subdivision * subdivision;

    addIndices(indices, subdivision, size);

    for (int face = 0; face < 1; face++) {
        auto start = glm::normalize(start_points[5]);
        auto end = glm::normalize(end_points[5]);

        const auto dd = (end - start) / ((float)subdivision - 1.0f);

        for (int i = 0; i < subdivision; i++) {
            for (int j = 0; j < subdivision; j++) {
                glm::vec3 mid = start + dd * glm::vec3(i, j,0.0f);

                glm::vec3 v = glm::normalize(mid);//toEuclid(mid);

                vertices.push_back(PositionNormalVertex{ v, v });

            }
        }
    }

    size += subdivision * subdivision;

    addIndices(indices, subdivision, size);


    return std::make_tuple(vertices, indices);
}