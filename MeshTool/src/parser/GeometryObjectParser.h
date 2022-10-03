#ifndef GEOMETRY_OBJECT_PARSER_H
#define GEOMETRY_OBJECT_PARSER_H

#include <string>

#include "../models/GeometryObject.h"

/// <summary>
/// Responsible for parsing of json string to GeometryObject and keeping an instance of GeometryObject until end of lifetime of this class' instance.
/// </summary>
class GeometryObjectParser {
public:
	void parse(const std::string& json);

	const GeometryObject& getGeometryObject() const;

	~GeometryObjectParser() = default;
private:
	GeometryObject geometryObject;
};

#endif // !GEOMETRY_OBJECT_PARSER_H
