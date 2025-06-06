#include "debug_draw_shapes_2d.h"
#include "core/object/class_db.h" // For ClassDB

DebugDrawShapes2D::DebugDrawShapes2D() {
    shape_type = SHAPE_CIRCLE;
    color = Color(1.0, 0.0, 0.0, 0.5); // Semi-transparent red
    filled = true;
    line_thickness = 1.0f;

    radius = 32.0f;

    rect_size = Vector2(64.0f, 64.0f);
    centered = true;

    line_end_point = Vector2(50.0f, 0.0f);

    // Default polygon (e.g., a small triangle)
    // polygon_points.push_back(Vector2(0, -20));
    // polygon_points.push_back(Vector2(-20, 20));
    // polygon_points.push_back(Vector2(20, 20));
    // Or leave empty, user must define.
}

void DebugDrawShapes2D::_notification(int p_what) {
    switch (p_what) {
        case NOTIFICATION_DRAW: {
            // The actual drawing is done in _draw() which is called automatically.
            // This notification is just an example of how you might react to it.
            // For this node, _draw() is sufficient.
        } break;
    }
}

void DebugDrawShapes2D::_draw() {
    // Ensure transform is up-to-date if drawing depends on it (Node2D handles this)
    switch (shape_type) {
        case SHAPE_CIRCLE: {
            if (filled) {
                draw_circle(Vector2(), radius, color);
            } else {
                // Draw an outlined circle using arcs or polyline
                int points = 32; // Number of segments for outline
                PackedVector2Array circle_points;
                circle_points.resize(points);
                for (int i = 0; i < points; i++) {
                    float angle = (float)i / points * Math_TAU;
                    circle_points.set(i, Vector2(cos(angle), sin(angle)) * radius);
                }
                draw_polyline(circle_points, color, line_thickness, true); // Antialiased
            }
        } break;
        case SHAPE_RECTANGLE: {
            Rect2 rect;
            if (centered) {
                rect = Rect2(-rect_size / 2.0, rect_size);
            } else {
                rect = Rect2(Vector2(), rect_size);
            }
            draw_rect(rect, color, filled, line_thickness);
        } break;
        case SHAPE_LINE: {
            draw_line(Vector2(), line_end_point, color, line_thickness, true); // Antialiased
        } break;
        case SHAPE_POLYGON: {
            if (polygon_points.size() < 2) { // Need at least 2 points for a line, 3 for a filled polygon
                break;
            }
            if (filled) {
                if (polygon_points.size() >= 3) {
                    PackedColorArray colors;
                    colors.push_back(color); // Single color for the whole polygon
                    draw_polygon(polygon_points, colors);
                }
            } else {
                draw_polyline(polygon_points, color, line_thickness, true); // Antialiased
            }
        } break;
        case SHAPE_MAX:
            // Should not happen
            break;
    }
}

// --- Setters and Getters ---
void DebugDrawShapes2D::set_shape_type(ShapeType p_type) {
    if (shape_type == p_type) return;
    shape_type = p_type;
    queue_redraw();
}

DebugDrawShapes2D::ShapeType DebugDrawShapes2D::get_shape_type() const {
    return shape_type;
}

void DebugDrawShapes2D::set_color(const Color &p_color) {
    if (color == p_color) return;
    color = p_color;
    queue_redraw();
}

Color DebugDrawShapes2D::get_color() const {
    return color;
}

void DebugDrawShapes2D::set_filled(bool p_filled) {
    if (filled == p_filled) return;
    filled = p_filled;
    queue_redraw();
}

bool DebugDrawShapes2D::is_filled() const {
    return filled;
}

void DebugDrawShapes2D::set_line_thickness(float p_thickness) {
    if (line_thickness == p_thickness) return;
    line_thickness = MAX(0.0f, p_thickness); // Ensure non-negative
    queue_redraw();
}

float DebugDrawShapes2D::get_line_thickness() const {
    return line_thickness;
}

void DebugDrawShapes2D::set_radius(float p_radius) {
    if (radius == p_radius) return;
    radius = MAX(0.0f, p_radius);
    queue_redraw();
}

float DebugDrawShapes2D::get_radius() const {
    return radius;
}

void DebugDrawShapes2D::set_rect_size(const Vector2 &p_size) {
    if (rect_size == p_size) return;
    rect_size = p_size; // Allow negative for flipping if desired, or add MAX(0,0)
    queue_redraw();
}

Vector2 DebugDrawShapes2D::get_rect_size() const {
    return rect_size;
}

void DebugDrawShapes2D::set_centered(bool p_centered) {
    if (centered == p_centered) return;
    centered = p_centered;
    queue_redraw();
}

bool DebugDrawShapes2D::is_centered() const {
    return centered;
}

void DebugDrawShapes2D::set_line_end_point(const Vector2 &p_end_point) {
    if (line_end_point == p_end_point) return;
    line_end_point = p_end_point;
    queue_redraw();
}

Vector2 DebugDrawShapes2D::get_line_end_point() const {
    return line_end_point;
}

void DebugDrawShapes2D::set_polygon_points(const PackedVector2Array &p_points) {
    // Note: Direct comparison of PackedVector2Array might be slow if they are large.
    // For simplicity, we'll redraw. For optimization, could compare content.
    polygon_points = p_points;
    queue_redraw();
}

PackedVector2Array DebugDrawShapes2D::get_polygon_points() const {
    return polygon_points;
}


// --- Binding ---
void DebugDrawShapes2D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_shape_type", "type"), &DebugDrawShapes2D::set_shape_type);
    ClassDB::bind_method(D_METHOD("get_shape_type"), &DebugDrawShapes2D::get_shape_type);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "shape_type", PROPERTY_HINT_ENUM, "Circle,Rectangle,Line,Polygon"), "set_shape_type", "get_shape_type");

    ClassDB::bind_method(D_METHOD("set_color", "color"), &DebugDrawShapes2D::set_color);
    ClassDB::bind_method(D_METHOD("get_color"), &DebugDrawShapes2D::get_color);
    ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color"), "set_color", "get_color");

    ClassDB::bind_method(D_METHOD("set_filled", "filled"), &DebugDrawShapes2D::set_filled);
    ClassDB::bind_method(D_METHOD("is_filled"), &DebugDrawShapes2D::is_filled);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "filled"), "set_filled", "is_filled");

    ClassDB::bind_method(D_METHOD("set_line_thickness", "thickness"), &DebugDrawShapes2D::set_line_thickness);
    ClassDB::bind_method(D_METHOD("get_line_thickness"), &DebugDrawShapes2D::get_line_thickness);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "line_thickness", PROPERTY_HINT_RANGE, "0,100,0.1,or_greater"), "set_line_thickness", "get_line_thickness");

    // Group for shape-specific properties
    ADD_GROUP("Circle", "circle_");
    ClassDB::bind_method(D_METHOD("set_radius", "radius"), &DebugDrawShapes2D::set_radius);
    ClassDB::bind_method(D_METHOD("get_radius"), &DebugDrawShapes2D::get_radius);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "circle_radius", PROPERTY_HINT_RANGE, "0,1000,0.1,or_greater"), "set_radius", "get_radius");

    ADD_GROUP("Rectangle", "rect_");
    ClassDB::bind_method(D_METHOD("set_rect_size", "size"), &DebugDrawShapes2D::set_rect_size);
    ClassDB::bind_method(D_METHOD("get_rect_size"), &DebugDrawShapes2D::get_rect_size);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "rect_size"), "set_rect_size", "get_rect_size");

    ClassDB::bind_method(D_METHOD("set_centered", "centered"), &DebugDrawShapes2D::set_centered);
    ClassDB::bind_method(D_METHOD("is_centered"), &DebugDrawShapes2D::is_centered);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "rect_centered"), "set_centered", "is_centered");

    ADD_GROUP("Line", "line_");
    ClassDB::bind_method(D_METHOD("set_line_end_point", "end_point"), &DebugDrawShapes2D::set_line_end_point);
    ClassDB::bind_method(D_METHOD("get_line_end_point"), &DebugDrawShapes2D::get_line_end_point);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "line_end_point"), "set_line_end_point", "get_line_end_point");

    ADD_GROUP("Polygon", "polygon_");
    ClassDB::bind_method(D_METHOD("set_polygon_points", "points"), &DebugDrawShapes2D::set_polygon_points);
    ClassDB::bind_method(D_METHOD("get_polygon_points"), &DebugDrawShapes2D::get_polygon_points);
    ADD_PROPERTY(PropertyInfo(Variant::PACKED_VECTOR2_ARRAY, "polygon_points"), "set_polygon_points", "get_polygon_points");

    BIND_ENUM_CONSTANT(SHAPE_CIRCLE);
    BIND_ENUM_CONSTANT(SHAPE_RECTANGLE);
    BIND_ENUM_CONSTANT(SHAPE_LINE);
    BIND_ENUM_CONSTANT(SHAPE_POLYGON);
    // SHAPE_MAX is internal, no need to bind usually
}