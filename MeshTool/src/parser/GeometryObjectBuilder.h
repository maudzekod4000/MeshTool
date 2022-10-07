#ifndef GEOMETRY_OBJECT_PARSER_H
#define GEOMETRY_OBJECT_PARSER_H

#include <string>
#include <memory>

#include "../models/GeometryObject.h"
#include "../models/Mesh.h"

class GeometryObjectBuilder {
public:
	void parse(const std::string& json);

	void fromMesh(std::unique_ptr<Mesh>& mesh);

	const GeometryObject& getGeometryObject() const;

	~GeometryObjectBuilder() = default;
private:
	GeometryObject geometryObject;
};

#endif // !GEOMETRY_OBJECT_PARSER_H
