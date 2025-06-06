#ifndef DEBUG_DRAW_SHAPES_2D_H
#define DEBUG_DRAW_SHAPES_2D_H

#include "scene/2d/node_2d.h"
#include "core/math/color.h"
#include "core/variant/typed_array.h" // For PackedVector2Array

class DebugDrawShapes2D : public Node2D {
    GDCLASS(DebugDrawShapes2D, Node2D);

public:
    enum ShapeType {
        SHAPE_CIRCLE,
        SHAPE_RECTANGLE,
        SHAPE_LINE,
        SHAPE_POLYGON,
        SHAPE_MAX // Helper for enum count or iteration if needed
    };

private:
    ShapeType shape_type;
    Color color;
    bool filled;
    float line_thickness;

    // Circle specific
    float radius;

    // Rectangle specific
    Vector2 rect_size;
    bool centered;

    // Line specific
    Vector2 line_end_point;

    // Polygon specific
    PackedVector2Array polygon_points;

protected:
    static void _bind_methods();
    void _notification(int p_what); // Will be used for NOTIFICATION_DRAW

public:
    DebugDrawShapes2D();

    void set_shape_type(ShapeType p_type);
    ShapeType get_shape_type() const;

    void set_color(const Color &p_color);
    Color get_color() const;

    void set_filled(bool p_filled);
    bool is_filled() const;

    void set_line_thickness(float p_thickness);
    float get_line_thickness() const;

    // Circle methods
    void set_radius(float p_radius);
    float get_radius() const;

    // Rectangle methods
    void set_rect_size(const Vector2 &p_size);
    Vector2 get_rect_size() const;

    void set_centered(bool p_centered);
    bool is_centered() const;

    // Line methods
    void set_line_end_point(const Vector2 &p_end_point);
    Vector2 get_line_end_point() const;

    // Polygon methods
    void set_polygon_points(const PackedVector2Array &p_points);
    PackedVector2Array get_polygon_points() const;

    virtual void _draw() override;
};

VARIANT_ENUM_CAST(DebugDrawShapes2D::ShapeType);

#endif // DEBUG_DRAW_SHAPES_2D_H