#ifndef DEBUG_DRAW_SHAPES_2D_H
#define DEBUG_DRAW_SHAPES_2D_H

#include "scene/2d/node_2d.h"
#include "scene/resources/style_box.h"
#include "core/templates/vector.h"

class DebugDrawShapes : public Node2D {
    GDCLASS(DebugDrawShapes, Node2D);



public:
    enum ShapeType {
        SHAPE_CIRCLE,
        SHAPE_RECT,
        SHAPE_LINE,
        SHAPE_POLYGON,
        SHAPE_ARC
    };

    struct Shape {
        ShapeType type;
        // For circle
        float radius = 0.0f;
        Vector2 offset = Vector2();
        // For rect
        Rect2 rect;
        // For line
        Vector2 from;
        Vector2 to;
        float width = 2.0f;
        // For polygons
        Vector<Vector2> points;
        Vector<Color> colors;
        // For arc
        Vector2 center;
        float arc_radius = 0.0f;
        float start_angle = 0.0f;
        float end_angle = 0.0f;
        int arc_points = 32;
        // Common
        Color color = Color(1,1,1,1);
    };

private:
    Vector<Shape> hitbox_shapes;

public:
    void set_hitbox(const Vector<Shape> &shapes);
    void set_hitbox_array(const Array &shapes);
    void clear_hitbox();
    void add_hitbox_circle(Vector2 offset, float radius, Color color);
    void add_hitbox_rect(Rect2 rect, Color color);
    void add_hitbox_line(Vector2 from, Vector2 to, Color color, float width = 2.0f);
    void add_hitbox_polygon(const Vector<Vector2> &points, Color color);
    void add_hitbox_polygon_colors(const Vector<Vector2> &points, const Vector<Color> &colors);
    void add_hitbox_arc(Vector2 center, float arc_radius, float start_angle, float end_angle, int arc_points, Color color, float width = 2.0f);
    void remove_hitbox_shape(int index);
    Array get_hitboxes() const;
    Array get_draw_commands() const;

protected:
    virtual void _draw();

protected:
    static void _bind_methods();

};

VARIANT_ENUM_CAST(DebugDrawShapes::ShapeType)

#endif

