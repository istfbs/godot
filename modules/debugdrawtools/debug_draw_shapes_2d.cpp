#include "debug_draw_shapes_2d.h"
#include "scene/main/canvas_item.h"

void DebugDrawShapes::set_hitbox(const Vector<Shape> &shapes) {
    hitbox_shapes = shapes;
}

void DebugDrawShapes::clear_hitbox() {
    hitbox_shapes.clear();
}

void DebugDrawShapes::draw_shapes() {
    for (const Shape &shape : hitbox_shapes) {
        switch (shape.type) {
            case SHAPE_CIRCLE:
                draw_circle(shape.offset, shape.radius, shape.color, false, 2.0, true);
                break;
            case SHAPE_RECT:
                draw_rect(shape.rect, shape.color, false, 2.0, true);
                break;
            case SHAPE_LINE:
                draw_line(shape.from, shape.to, shape.color, shape.width, true);
                break;
            case SHAPE_POLYGON:
                if (shape.colors.size() == shape.points.size() && shape.points.size() > 2) {
                    draw_polygon(shape.points, shape.colors);
                } else if (shape.points.size() > 2) {
                    Vector<Color> fill_colors;
                    fill_colors.resize(shape.points.size());
                    for (int i = 0; i < fill_colors.size(); ++i) fill_colors.write[i] = shape.color;
                    draw_polygon(shape.points, fill_colors);
                }
                break;
            case SHAPE_ARC:
                draw_arc(shape.center, shape.arc_radius, shape.start_angle, shape.end_angle, shape.arc_points, shape.color, shape.width, true);
                break;
        }
    }
}

void DebugDrawShapes::add_hitbox_circle(Vector2 offset, float radius, Color color) {
    Shape shape;
    shape.type = SHAPE_CIRCLE;
    shape.offset = offset;
    shape.radius = radius;
    shape.color = color;
    hitbox_shapes.push_back(shape);
}

void DebugDrawShapes::add_hitbox_rect(Rect2 rect, Color color) {
    Shape shape;
    shape.type = SHAPE_RECT;
    shape.rect = rect;
    shape.color = color;
    hitbox_shapes.push_back(shape);
}

void DebugDrawShapes::add_hitbox_line(Vector2 from, Vector2 to, Color color, float width) {
    Shape shape;
    shape.type = SHAPE_LINE;
    shape.from = from;
    shape.to = to;
    shape.color = color;
    shape.width = width;
    hitbox_shapes.push_back(shape);
}

void DebugDrawShapes::add_hitbox_polygon(const Vector<Vector2> &points, Color color) {
    Shape shape;
    shape.type = SHAPE_POLYGON;
    shape.points = points;
    shape.color = color;
    hitbox_shapes.push_back(shape);
}

void DebugDrawShapes::add_hitbox_polygon_colors(const Vector<Vector2> &points, const Vector<Color> &colors) {
    Shape shape;
    shape.type = SHAPE_POLYGON;
    shape.points = points;
    shape.colors = colors;
    hitbox_shapes.push_back(shape);
}

void DebugDrawShapes::add_hitbox_arc(Vector2 center, float arc_radius, float start_angle, float end_angle, int arc_points, Color color, float width) {
    Shape shape;
    shape.type = SHAPE_ARC;
    shape.center = center;
    shape.arc_radius = arc_radius;
    shape.start_angle = start_angle;
    shape.end_angle = end_angle;
    shape.arc_points = arc_points;
    shape.color = color;
    shape.width = width;
    hitbox_shapes.push_back(shape);
}

void DebugDrawShapes::remove_hitbox_shape(int index) {
    if (index >= 0 && index < hitbox_shapes.size()) {
        hitbox_shapes.remove_at(index);
    }
}

void DebugDrawShapes::set_hitbox_array(const Array &shapes) {
    hitbox_shapes.clear();
    for (int i = 0; i < shapes.size(); ++i) {
        Dictionary dict = shapes[i];
        Shape shape;
        if (!dict.has("type")) continue;
        shape.type = (ShapeType)(int)dict["type"];
        if (dict.has("color")) shape.color = dict["color"];
        switch (shape.type) {
            case SHAPE_CIRCLE:
                if (dict.has("radius")) shape.radius = dict["radius"];
                if (dict.has("offset")) shape.offset = dict["offset"];
                break;
            case SHAPE_RECT:
                if (dict.has("rect")) shape.rect = dict["rect"];
                break;
            case SHAPE_LINE:
                if (dict.has("from")) shape.from = dict["from"];
                if (dict.has("to")) shape.to = dict["to"];
                if (dict.has("width")) shape.width = dict["width"];
                break;
            case SHAPE_POLYGON:
                if (dict.has("points")) shape.points = dict["points"];
                if (dict.has("colors")) shape.colors = dict["colors"];
                break;
            case SHAPE_ARC:
                if (dict.has("center")) shape.center = dict["center"];
                if (dict.has("arc_radius")) shape.arc_radius = dict["arc_radius"];
                if (dict.has("start_angle")) shape.start_angle = dict["start_angle"];
                if (dict.has("end_angle")) shape.end_angle = dict["end_angle"];
                if (dict.has("arc_points")) shape.arc_points = dict["arc_points"];
                if (dict.has("width")) shape.width = dict["width"];
                break;
        }
        hitbox_shapes.push_back(shape);
    }
}

void DebugDrawShapes::_bind_methods() {
    ClassDB::bind_method(D_METHOD("clear_hitbox"), &DebugDrawShapes::clear_hitbox);
    ClassDB::bind_method(D_METHOD("draw_shapes"), &DebugDrawShapes::draw_shapes);
    ClassDB::bind_method(D_METHOD("add_hitbox_circle", "offset", "radius", "color"), &DebugDrawShapes::add_hitbox_circle);
    ClassDB::bind_method(D_METHOD("add_hitbox_rect", "rect", "color"), &DebugDrawShapes::add_hitbox_rect);
    ClassDB::bind_method(D_METHOD("add_hitbox_line", "from", "to", "color", "width"), &DebugDrawShapes::add_hitbox_line);
    ClassDB::bind_method(D_METHOD("add_hitbox_polygon", "points", "color"), &DebugDrawShapes::add_hitbox_polygon);
    ClassDB::bind_method(D_METHOD("add_hitbox_polygon_colors", "points", "colors"), &DebugDrawShapes::add_hitbox_polygon_colors);
    ClassDB::bind_method(D_METHOD("add_hitbox_arc", "center", "arc_radius", "start_angle", "end_angle", "arc_points", "color", "width"), &DebugDrawShapes::add_hitbox_arc);
    ClassDB::bind_method(D_METHOD("remove_hitbox_shape", "index"), &DebugDrawShapes::remove_hitbox_shape);
    ClassDB::bind_method(D_METHOD("set_hitbox_array", "shapes"), &DebugDrawShapes::set_hitbox_array);

    BIND_ENUM_CONSTANT(SHAPE_CIRCLE);
    BIND_ENUM_CONSTANT(SHAPE_RECT);
    BIND_ENUM_CONSTANT(SHAPE_LINE);
    BIND_ENUM_CONSTANT(SHAPE_POLYGON);
    BIND_ENUM_CONSTANT(SHAPE_ARC);
}