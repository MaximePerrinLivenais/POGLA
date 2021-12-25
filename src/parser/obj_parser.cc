#include "obj_parser.hh"
#include <fstream>
#include <iostream>

namespace parser
{
    void parse_line(ObjData& data, ObjData& faces, const std::string& line)
    {
        // Vertex position / normal values / uv positions
        float x, y, z;

        // Parse vertex position
        if (std::sscanf(line.c_str(), "v %f %f %f", &x, &y, &z))
        {
            data.points.push_back(x);
            data.points.push_back(y);
            data.points.push_back(z);

            return;
        }

        // Parse vertex uv position
        if (std::sscanf(line.c_str(), "vt %f %f", &x, &y))
        {
            data.uvs.push_back(x);
            data.uvs.push_back(y);

            return;
        }

        // Parse vertex normal
        if (std::sscanf(line.c_str(), "vn %f %f %f", &x, &y, &z))
        {
            data.normals.push_back(x);
            data.normals.push_back(y);
            data.normals.push_back(z);

            return;
        }

        size_t v1, vt1, vn1;
        size_t v2, vt2, vn2;
        size_t v3, vt3, vn3;

        // Handle face's vertex index
        // Copies vertices for now, maybe should do something smarter
        if (std::sscanf(line.c_str(), "f %lu/%lu/%lu %lu/%lu/%lu %lu/%lu/%lu",
                        &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3))
        {
            // Add the three cooridanes of the three points
            faces.points.push_back(data.points[(v1 - 1) * 3 + 0]);
            faces.points.push_back(data.points[(v1 - 1) * 3 + 1]);
            faces.points.push_back(data.points[(v1 - 1) * 3 + 2]);

            faces.points.push_back(data.points[(v2 - 1) * 3 + 0]);
            faces.points.push_back(data.points[(v2 - 1) * 3 + 1]);
            faces.points.push_back(data.points[(v2 - 1) * 3 + 2]);

            faces.points.push_back(data.points[(v3 - 1) * 3 + 0]);
            faces.points.push_back(data.points[(v3 - 1) * 3 + 1]);
            faces.points.push_back(data.points[(v3 - 1) * 3 + 2]);

            // Add the three normals for each vertex
            faces.normals.push_back(data.normals[(vn1 - 1) * 3 + 0]);
            faces.normals.push_back(data.normals[(vn1 - 1) * 3 + 1]);
            faces.normals.push_back(data.normals[(vn1 - 1) * 3 + 2]);

            faces.normals.push_back(data.normals[(vn2 - 1) * 3 + 0]);
            faces.normals.push_back(data.normals[(vn2 - 1) * 3 + 1]);
            faces.normals.push_back(data.normals[(vn2 - 1) * 3 + 2]);

            faces.normals.push_back(data.normals[(vn3 - 1) * 3 + 0]);
            faces.normals.push_back(data.normals[(vn3 - 1) * 3 + 1]);
            faces.normals.push_back(data.normals[(vn3 - 1) * 3 + 2]);

            // Add the colors of each vertex (just using the values of the
            // normals)
            faces.colors.push_back(std::abs(data.normals[(vn1 - 1) * 3 + 0]));
            faces.colors.push_back(std::abs(data.normals[(vn1 - 1) * 3 + 1]));
            faces.colors.push_back(std::abs(data.normals[(vn1 - 1) * 3 + 2]));

            faces.colors.push_back(std::abs(data.normals[(vn2 - 1) * 3 + 0]));
            faces.colors.push_back(std::abs(data.normals[(vn2 - 1) * 3 + 1]));
            faces.colors.push_back(std::abs(data.normals[(vn2 - 1) * 3 + 2]));

            faces.colors.push_back(std::abs(data.normals[(vn3 - 1) * 3 + 0]));
            faces.colors.push_back(std::abs(data.normals[(vn3 - 1) * 3 + 1]));
            faces.colors.push_back(std::abs(data.normals[(vn3 - 1) * 3 + 2]));

            // Add uvs of each vertex
            faces.uvs.push_back(data.uvs[(vt1 - 1) * 2 + 0]);
            faces.uvs.push_back(data.uvs[(vt1 - 1) * 2 + 1]);

            faces.uvs.push_back(data.uvs[(vt2 - 1) * 2 + 0]);
            faces.uvs.push_back(data.uvs[(vt2 - 1) * 2 + 1]);

            faces.uvs.push_back(data.uvs[(vt3 - 1) * 2 + 0]);
            faces.uvs.push_back(data.uvs[(vt3 - 1) * 2 + 1]);

            return;
        }
    }

    ObjData parse_obj(std::string file)
    {
        ObjData data;
        ObjData faces;

        std::fstream input(file);

        if (!input.is_open())
        {
            std::cerr << "Can't open file " << file << "\n";
            return faces;
        }

        for (std::string line; std::getline(input, line);)
            parse_line(data, faces, line);

        return faces;
    }
} // namespace parser
