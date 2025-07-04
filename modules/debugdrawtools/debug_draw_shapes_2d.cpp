#include "debug_draw_shapes_2d.h"
#include "scene/main/canvas_item.h"
#include "scene/resources/style_box.h"
#include "core/templates/vector.h"

void DebugDrawShapes::set_hitbox(const Vector<Shape> &shapes) {
    hitbox_shapes = shapes;
    queue_redraw(); 
}



void DebugDrawShapes::clear_hitbox() {
    hitbox_shapes.clear();
    queue_redraw(); 
}

void DebugDrawShapes::_draw() {
    draw_circle(Vector2(100, 100), 50, Color::named("red"), true, -1, false);
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
    queue_redraw(); 
}

void DebugDrawShapes::add_hitbox_rect(Rect2 rect, Color color) {
    Shape shape;
    shape.type = SHAPE_RECT;
    shape.rect = rect;
    shape.color = color;
    hitbox_shapes.push_back(shape);
    queue_redraw(); 
}

void DebugDrawShapes::add_hitbox_line(Vector2 from, Vector2 to, Color color, float width) {
    Shape shape;
    shape.type = SHAPE_LINE;
    shape.from = from;
    shape.to = to;
    shape.color = color;
    shape.width = width;
    hitbox_shapes.push_back(shape);
    queue_redraw(); 
}

void DebugDrawShapes::add_hitbox_polygon(const Vector<Vector2> &points, Color color) {
    Shape shape;
    shape.type = SHAPE_POLYGON;
    shape.points = points;
    shape.color = color;
    hitbox_shapes.push_back(shape);
    queue_redraw(); 
}

void DebugDrawShapes::add_hitbox_polygon_colors(const Vector<Vector2> &points, const Vector<Color> &colors) {
    Shape shape;
    shape.type = SHAPE_POLYGON;
    shape.points = points;
    shape.colors = colors;
    hitbox_shapes.push_back(shape);
    queue_redraw(); 
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
    queue_redraw(); 
}

void DebugDrawShapes::remove_hitbox_shape(int index) {
    if (index >= 0 && index < hitbox_shapes.size()) {
        hitbox_shapes.remove_at(index);
        queue_redraw(); 
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
    queue_redraw(); 
}

Array DebugDrawShapes::get_hitboxes() const {
    Array arr;
    for (const Shape &shape : hitbox_shapes) {
        Dictionary dict;
        dict["type"] = (int)shape.type;
        dict["color"] = shape.color;
        switch (shape.type) {
            case SHAPE_CIRCLE:
                dict["offset"] = shape.offset;
                dict["radius"] = shape.radius;
                break;
            case SHAPE_RECT:
                dict["rect"] = shape.rect;
                break;
            case SHAPE_LINE:
                dict["from"] = shape.from;
                dict["to"] = shape.to;
                dict["width"] = shape.width;
                break;
            case SHAPE_POLYGON:
                dict["points"] = shape.points;
                dict["colors"] = shape.colors;
                break;
            case SHAPE_ARC:
                dict["center"] = shape.center;
                dict["arc_radius"] = shape.arc_radius;
                dict["start_angle"] = shape.start_angle;
                dict["end_angle"] = shape.end_angle;
                dict["arc_points"] = shape.arc_points;
                dict["width"] = shape.width;
                break;
        }
        arr.append(dict);
    }
    return arr;
}

Array DebugDrawShapes::get_draw_commands() const {
    Array commands;
    for (const Shape &shape : hitbox_shapes) {
        String cmd;
        switch (shape.type) {
            case SHAPE_CIRCLE:
                cmd = vformat("draw_circle(%s, %f, %s)", 
                    shape.offset, shape.radius, shape.color);
                break;
            case SHAPE_RECT:
                cmd = vformat("draw_rect(%s, %s)", 
                    shape.rect, shape.color);
                break;
            case SHAPE_LINE:
                cmd = vformat("draw_line(%s, %s, %s, %f)", 
                    shape.from, shape.to, shape.color, shape.width);
                break;
            case SHAPE_POLYGON: {
                String colors_str;
                if (shape.colors.size() > 0) {
                    PackedStringArray color_strs;
                    for (int i = 0; i < shape.colors.size(); ++i) {
                        color_strs.append(String(shape.colors[i]));
                    }
                    colors_str = "[" + String(", ").join(color_strs) + "]";
                } else {
                    colors_str = "[default color]";
                }
                cmd = vformat("draw_polygon(%s, %s)", shape.points, colors_str);
                break;
            }
            case SHAPE_ARC:
                cmd = vformat("draw_arc(%s, %f, %f, %f, %d, %s, %f)", 
                    shape.center, shape.arc_radius, shape.start_angle, shape.end_angle, shape.arc_points, shape.color, shape.width);
                break;
        }
        commands.append(cmd);
    }
    return commands;
}

void DebugDrawShapes::_bind_methods() {
    ClassDB::bind_method(D_METHOD("clear_hitbox"), &DebugDrawShapes::clear_hitbox);
    ClassDB::bind_method(D_METHOD("add_hitbox_circle", "offset", "radius", "color"), &DebugDrawShapes::add_hitbox_circle);
    ClassDB::bind_method(D_METHOD("add_hitbox_rect", "rect", "color"), &DebugDrawShapes::add_hitbox_rect);
    ClassDB::bind_method(D_METHOD("add_hitbox_line", "from", "to", "color", "width"), &DebugDrawShapes::add_hitbox_line);
    ClassDB::bind_method(D_METHOD("add_hitbox_polygon", "points", "color"), &DebugDrawShapes::add_hitbox_polygon);
    ClassDB::bind_method(D_METHOD("add_hitbox_polygon_colors", "points", "colors"), &DebugDrawShapes::add_hitbox_polygon_colors);
    ClassDB::bind_method(D_METHOD("add_hitbox_arc", "center", "arc_radius", "start_angle", "end_angle", "arc_points", "color", "width"), &DebugDrawShapes::add_hitbox_arc);
    ClassDB::bind_method(D_METHOD("remove_hitbox_shape", "index"), &DebugDrawShapes::remove_hitbox_shape);
    ClassDB::bind_method(D_METHOD("set_hitbox_array", "shapes"), &DebugDrawShapes::set_hitbox_array);
    ClassDB::bind_method(D_METHOD("get_hitboxes"), &DebugDrawShapes::get_hitboxes);
    ClassDB::bind_method(D_METHOD("get_draw_commands"), &DebugDrawShapes::get_draw_commands);

    BIND_ENUM_CONSTANT(SHAPE_CIRCLE);
    BIND_ENUM_CONSTANT(SHAPE_RECT);
    BIND_ENUM_CONSTANT(SHAPE_LINE);
    BIND_ENUM_CONSTANT(SHAPE_POLYGON);
    BIND_ENUM_CONSTANT(SHAPE_ARC);
}

