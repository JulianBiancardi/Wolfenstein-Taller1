#include "ray_casting.h"

#include <cmath>

#define CELL_SIZE 64
#define WALL 1

Point first_quad_x(Map& map, const Point& origin, double tg);
Point first_quad_y(Map& map, const Point& origin, double tg);

Point second_quad_x(Map& map, const Point& origin, double tg);
Point second_quad_y(Map& map, const Point& origin, double tg);

Point third_quad_x(Map& map, const Point& origin, double tg);
Point third_quad_y(Map& map, const Point& origin, double tg);

Point forth_quad_x(Map& map, const Point& origin, double tg);
Point forth_quad_y(Map& map, const Point& origin, double tg);

Point RayCasting::get_intersection(Map& map, Ray& ray) {
  double angle = ray.get_angle();

  if (angle == 0) {
    return RayCasting::horizontal_axis(map, ray);
  } else if (angle > 0 && angle < M_PI_2) {
    return RayCasting::first_quad(map, ray);
  } else if (angle == M_PI_2) {
    return RayCasting::vertical_axis(map, ray);
  } else if (angle > M_PI_2 && angle < M_PI) {
    return RayCasting::second_quad(map, ray);
  } else if (angle == M_PI) {
    return RayCasting::horizontal_axis(map, ray);
  } else if (angle > M_PI && angle < 3 * M_PI_2) {
    return RayCasting::third_quad(map, ray);
  } else if (angle == 3 * M_PI_2) {
    return vertical_axis(map, ray);
  } else if (angle > 3 * M_PI_2 && angle <= 2 * M_PI) {
    return RayCasting::forth_quad(map, ray);
  } else {
    return Point(0, 0);  // TODO Throw Exception
  }
}

double RayCasting::get_scaling_factor(Ray& ray, Ray& player_direction,
                                      Point& intersection_point) {
  double player_angle = player_direction.get_angle();
  double ray_angle = ray.get_angle();
  double ray_offset = (ray_angle - player_angle);
  double intersection_distance =
      Point::distance(ray.get_origin(), intersection_point);

  double distance_to_player_sight = intersection_distance * cos(ray_offset);

  // TODO Move the scaling constant to here and replace 1.
  return 1 / distance_to_player_sight;

  // TODO Draw from back to front
  // Use similar scaling for sprites
}

Point RayCasting::horizontal_axis(Map& map, Ray& ray) {
  Point origin = ray.get_origin();

  double dx = std::fmod(origin.getX(), 1);

  if (ray.get_angle() == 0) {
    // Point coords for first intersection
    double x = origin.getX() + (1 - dx);
    double y = origin.getY();

    while (true) {
      try {
        if (map.is_wall(x, y)) {
          return Point(x, y);
        }
      } catch (int FIXME) {
        return Point(x, y);
      }

      x = x + 1;
    }
  } else {
    // Point coords for first intersection
    double x = origin.getX() - dx - 1;
    double y = origin.getY();

    while (true) {
      try {
        if (map.is_wall(x, y)) {
          return Point(x, y);
        }
      } catch (int FIXME) {
        return Point(x, y);
      }

      x = x - 1;
    }
  }
}

Point RayCasting::vertical_axis(Map& map, Ray& ray) {
  Point origin = ray.get_origin();

  double dy = std::fmod(origin.getY(), 1);

  if (ray.get_angle() == M_PI_2) {
    // Point coords for first intersection
    double x = origin.getX();
    double y = origin.getY() - dy - 1;

    while (true) {
      try {
        if (map.is_wall(x, y)) {
          return Point(x, y);
        }
      } catch (int FIXME) {
        return Point(x, y);
      }

      y = y - 1;
    }
  } else {
    // Point coords for first intersection
    double x = origin.getX();
    double y = origin.getY() + (1 - dy);

    while (true) {
      try {
        if (map.is_wall(x, y)) {
          return Point(x, y);
        }
      } catch (int FIXME) {
        return Point(x, y);
      }

      y = y + 1;
    }
  }
}

Point RayCasting::first_quad(Map& map, Ray& ray) {
  Point origin = ray.get_origin();

  // Precalculate tangent to avoid multiple calls.
  double tg = fabs(tan(ray.get_angle()));

  Point x_intersection = first_quad_x(map, origin, tg);
  Point y_intersection = first_quad_y(map, origin, tg);

  double distance1 = Point::distance(ray.get_origin(), x_intersection);
  double distance2 = Point::distance(ray.get_origin(), y_intersection);
  return distance1 < distance2 ? x_intersection : y_intersection;
}

Point first_quad_x(Map& map, const Point& origin, double tg) {
  // Point coord for first X intersection
  double x;
  double y;
  double dx = std::modf(origin.getX(), &x);

  x = x + 1;
  y = origin.getY() - (1 - dx) * tg;

  double y_step = tg;

  while (true) {
    Point x_intersection(x, y);
    try {
      if (map.is_wall(x, y)) {
        return x_intersection;
      }
    } catch (int a) {
      return x_intersection;
    }

    x = x + 1;
    y = y - y_step;
  }
}

Point first_quad_y(Map& map, const Point& origin, double tg) {
  // Point coord for first Y intersection
  double x;
  double y;
  double dy = std::modf(origin.getY(), &y);

  x = origin.getX() + dy / tg;
  y = y - 0.001;

  double x_step = 1 / tg;

  while (true) {
    Point y_intersection(x, y);
    try {
      if (map.is_wall(x, y)) {
        return y_intersection;
      }
    } catch (int a) {
      return y_intersection;
    }

    x = x + x_step;
    y = y - 1;
  }
}

Point RayCasting::second_quad(Map& map, Ray& ray) {
  Point origin = ray.get_origin();

  // Precalculate tangent to avoid multiple calls.
  double tg = fabs(tan(ray.get_angle()));

  Point x_intersection = second_quad_x(map, origin, tg);
  Point y_intersection = second_quad_y(map, origin, tg);

  double distance1 = Point::distance(ray.get_origin(), x_intersection);
  double distance2 = Point::distance(ray.get_origin(), y_intersection);
  return distance1 < distance2 ? x_intersection : y_intersection;
}

Point second_quad_x(Map& map, const Point& origin, double tg) {
  // Point coord for first X intersection
  double x;
  double y;
  double dx = std::modf(origin.getX(), &x);

  x = x - 0.0001;
  y = origin.getY() - dx * tg;

  double y_step = tg;

  while (true) {
    Point x_intersection(x, y);
    try {
      if (map.is_wall(x, y)) {
        return x_intersection;
      }
    } catch (int FIXME) {
      return x_intersection;
    }

    x = x - 1;
    y = y - y_step;
  }
}

Point second_quad_y(Map& map, const Point& origin, double tg) {
  // Point coord for first Y intersection
  double x;
  double y;
  double dy = std::modf(origin.getY(), &y);

  x = origin.getX() - dy / tg;
  y = y - 0.0001;

  double x_step = 1 / tg;

  while (true) {
    Point y_intersection(x, y);
    try {
      if (map.is_wall(x, y)) {
        return y_intersection;
      }
    } catch (int FIXME) {
      return y_intersection;
    }

    x = x - x_step;
    y = y - 1;
  }
}

Point RayCasting::third_quad(Map& map, Ray& ray) {
  Point origin = ray.get_origin();

  // Precalculate tangent to avoid multiple calls.
  double tg = fabs(tan(ray.get_angle()));

  // Points of intersection
  Point x_intersection = third_quad_x(map, origin, tg);
  Point y_intersection = third_quad_y(map, origin, tg);

  double distance1 = Point::distance(ray.get_origin(), x_intersection);
  double distance2 = Point::distance(ray.get_origin(), y_intersection);
  return distance1 < distance2 ? x_intersection : y_intersection;
}

Point third_quad_x(Map& map, const Point& origin, double tg) {
  // Point coord for first X intersection
  double x;
  double y;
  double dx = std::modf(origin.getX(), &x);

  x = x - 0.0001;
  y = origin.getY() + dx * tg;

  double y_step = tg;

  while (true) {
    Point x_intersection(x, y);
    try {
      if (map.is_wall(x, y)) {
        return x_intersection;
      }
    } catch (int FIXME) {
      return x_intersection;
    }

    x = x - 1;
    y = y + y_step;
  }
}

Point third_quad_y(Map& map, const Point& origin, double tg) {
  // Point coord for first Y intersection
  double x;
  double y;
  double dy = std::modf(origin.getY(), &y);

  x = origin.getX() - (1 - dy) / tg;
  y = y + 1;

  double x_step = 1 / tg;

  while (true) {
    Point y_intersection(x, y);
    try {
      if (map.is_wall(x, y)) {
        return y_intersection;
      }
    } catch (int FIXME) {
      return y_intersection;
    }

    x = x - x_step;
    y = y + 1;
  }
}

Point RayCasting::forth_quad(Map& map, Ray& ray) {
  Point origin = ray.get_origin();

  // Precalculate tangent to avoid multiple calls.
  double tg = fabs(tan(ray.get_angle()));

  Point y_intersection = forth_quad_y(map, origin, tg);
  Point x_intersection = forth_quad_x(map, origin, tg);

  double distance1 = Point::distance(ray.get_origin(), x_intersection);
  double distance2 = Point::distance(ray.get_origin(), y_intersection);

  return distance1 < distance2 ? x_intersection : y_intersection;
}

Point forth_quad_x(Map& map, const Point& origin, double tg) {
  // Point coord for first X intersection
  double x;
  double y;
  double dx = std::modf(origin.getX(), &x);

  x = x + 1;
  y = origin.getY() + (1 - dx) * tg;

  double y_step = tg;

  while (true) {
    Point x_intersection(x, y);
    try {
      if (map.is_wall(x, y)) {
        return x_intersection;
      }
    } catch (int FIXME) {
      return x_intersection;
    }

    x = x + 1;
    y = y + y_step;
  }
}

Point forth_quad_y(Map& map, const Point& origin, double tg) {
  // Point coord for first Y intersection
  double x;
  double y;
  double dy = std::modf(origin.getY(), &y);

  x = origin.getX() + (1 - dy) / tg;
  y = y + 1;

  double x_step = 1 / tg;

  while (true) {
    Point y_intersection(x, y);
    try {
      if (map.is_wall(x, y)) {
        return y_intersection;
      }
    } catch (int FIXME) {
      return y_intersection;
    }

    x = x + x_step;
    y = y + 1;
  }
}
