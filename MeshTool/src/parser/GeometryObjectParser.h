#ifndef GEOMETRY_OBJECT_PARSER_H
#define GEOMETRY_OBJECT_PARSER_H

#include <string>

#include "../models/GeometryObject.h"

class GeometryObjectParser {
public:
	void parse(const std::string& json);

	const GeometryObject& getGeometryObject() const;

	~GeometryObjectParser() = default;
private:
	GeometryObject geometryObject;
};

#endif // !GEOMETRY_OBJECT_PARSER_H
