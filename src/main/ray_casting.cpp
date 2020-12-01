#include "ray_casting.h"

#include <cmath>

#define CELL_SIZE 64
#define WALL 1

Point first_quad_x(Matrix<int>& map, const Point& origin, double tg);
Point first_quad_y(Matrix<int>& map, const Point& origin, double tg);

Point second_quad_x(Matrix<int>& map, const Point& origin, double tg);
Point second_quad_y(Matrix<int>& map, const Point& origin, double tg);

Point third_quad_x(Matrix<int>& map, const Point& origin, double tg);
Point third_quad_y(Matrix<int>& map, const Point& origin, double tg);

Point forth_quad_x(Matrix<int>& map, const Point& origin, double tg);
Point forth_quad_y(Matrix<int>& map, const Point& origin, double tg);

Point RayCasting::get_intersection(Matrix<int>& map, Ray& ray) {
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
    printf("ANGLE: %f\n", angle);
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

Point RayCasting::horizontal_axis(Matrix<int>& map, Ray& ray) {
  Point origin = ray.get_origin();

  size_t dx = origin.getX() % CELL_SIZE;

  if (ray.get_angle() == 0) {
    // Point coords for first intersection
    double x = origin.getX() + (CELL_SIZE - dx);
    double y = origin.getY();

    while (true) {
      try {
        if (map((int)x, (int)y) >= WALL) {
          return Point(x, y);
        }
      } catch (int FIXME) {
        return Point(x, y);
      }

      x = x + CELL_SIZE;
    }
  } else {
    // Point coords for first intersection
    double x = origin.getX() - dx - 1;
    double y = origin.getY();

    while (true) {
      try {
        if (map((int)x, (int)y) >= WALL) {
          return Point(x, y);
        }
      } catch (int FIXME) {
        return Point(x, y);
      }

      x = x - CELL_SIZE;
    }
  }
}

Point RayCasting::vertical_axis(Matrix<int>& map, Ray& ray) {
  Point origin = ray.get_origin();

  size_t dy = origin.getY() % CELL_SIZE;

  if (ray.get_angle() == M_PI_2) {
    // Point coords for first intersection
    double x = origin.getX();
    double y = origin.getY() - dy - 1;

    while (true) {
      try {
        if (map((int)x, (int)y) >= WALL) {
          return Point(x, y);
        }
      } catch (int FIXME) {
        return Point(x, y);
      }

      y = y - CELL_SIZE;
    }
  } else {
    // Point coords for first intersection
    double x = origin.getX();
    double y = origin.getY() + (CELL_SIZE - dy);

    while (true) {
      try {
        if (map((int)x, (int)y) >= WALL) {
          return Point(x, y);
        }
      } catch (int FIXME) {
        return Point(x, y);
      }

      y = y + CELL_SIZE;
    }
  }
}

Point RayCasting::first_quad(Matrix<int>& map, Ray& ray) {
  Point origin = ray.get_origin();

  // Precalculate tangent to avoid multiple calls.
  double tg = fabs(tan(ray.get_angle()));

  Point x_intersection = first_quad_x(map, origin, tg);
  Point y_intersection = first_quad_y(map, origin, tg);

  double distance1 = Point::distance(ray.get_origin(), x_intersection);
  double distance2 = Point::distance(ray.get_origin(), y_intersection);
  return distance1 < distance2 ? x_intersection : y_intersection;
}

Point first_quad_x(Matrix<int>& map, const Point& origin, double tg) {
  size_t dx = origin.getX() % CELL_SIZE;

  // Point coord for first X intersection
  double x = origin.getX() + (CELL_SIZE - dx);
  double y = origin.getY() - (CELL_SIZE - dx) * tg;

  double y_step = CELL_SIZE * tg;

  while (true) {
    Point x_intersection(x, y);
    try {
      if (map((int)x, (int)y) >= WALL) {
        return x_intersection;
      }
    } catch (int a) {
      return x_intersection;
    }

    x = x + CELL_SIZE;
    y = y - y_step;
  }
}

Point first_quad_y(Matrix<int>& map, const Point& origin, double tg) {
  size_t dy = origin.getY() % CELL_SIZE;

  // Point coord for first Y intersection
  double x = origin.getX() + dy / tg;
  double y = origin.getY() - dy - 1;

  double x_step = CELL_SIZE / tg;

  while (true) {
    Point y_intersection(x, y);
    try {
      if (map((int)x, (int)y) >= WALL) {
        return y_intersection;
      }
    } catch (int a) {
      return y_intersection;
    }

    x = x + x_step;
    y = y - CELL_SIZE;
  }
}

Point RayCasting::second_quad(Matrix<int>& map, Ray& ray) {
  Point origin = ray.get_origin();

  // Precalculate tangent to avoid multiple calls.
  double tg = fabs(tan(ray.get_angle()));

  Point x_intersection = second_quad_x(map, origin, tg);
  Point y_intersection = second_quad_y(map, origin, tg);

  double distance1 = Point::distance(ray.get_origin(), x_intersection);
  double distance2 = Point::distance(ray.get_origin(), y_intersection);
  return distance1 < distance2 ? x_intersection : y_intersection;
}

Point second_quad_x(Matrix<int>& map, const Point& origin, double tg) {
  size_t dx = origin.getX() % CELL_SIZE;

  // Point coord for first X intersection
  double x = origin.getX() - dx - 1;
  double y = origin.getY() - dx * tg;

  double y_step = CELL_SIZE * tg;

  while (true) {
    Point x_intersection(x, y);
    try {
      if (map((int)x, (int)y) >= WALL) {
        return x_intersection;
      }
    } catch (int FIXME) {
      return x_intersection;
    }

    x = x - CELL_SIZE;
    y = y - y_step;
  }
}

Point second_quad_y(Matrix<int>& map, const Point& origin, double tg) {
  size_t dy = origin.getY() % CELL_SIZE;

  // Point coord for first Y intersection
  double x = origin.getX() - dy / tg;
  double y = origin.getY() - dy - 1;

  double x_step = CELL_SIZE / tg;

  while (true) {
    Point y_intersection(x, y);
    try {
      if (map((int)x, (int)y) >= WALL) {
        return y_intersection;
      }
    } catch (int FIXME) {
      return y_intersection;
    }

    x = x - x_step;
    y = y - CELL_SIZE;
  }
}

Point RayCasting::third_quad(Matrix<int>& map, Ray& ray) {
  Point origin = ray.get_origin();

  size_t dx = origin.getX() % CELL_SIZE;
  size_t dy = origin.getY() % CELL_SIZE;

  // Precalculate tangent to avoid multiple calls.
  double tg = fabs(tan(ray.get_angle()));

  // Points of intersection
  Point x_intersection = third_quad_x(map, origin, tg);
  Point y_intersection = third_quad_y(map, origin, tg);

  double distance1 = Point::distance(ray.get_origin(), x_intersection);
  double distance2 = Point::distance(ray.get_origin(), y_intersection);
  return distance1 < distance2 ? x_intersection : y_intersection;
}

Point third_quad_x(Matrix<int>& map, const Point& origin, double tg) {
  size_t dx = origin.getX() % CELL_SIZE;

  // Point coord for first X intersection
  double x = origin.getX() - dx - 1;
  double y = origin.getY() + dx * tg;

  double y_step = CELL_SIZE * tg;

  while (true) {
    Point x_intersection(x, y);
    try {
      if (map((int)x, (int)y) >= WALL) {
        return x_intersection;
      }
    } catch (int FIXME) {
      return x_intersection;
    }

    x = x - CELL_SIZE;
    y = y + y_step;
  }
}

Point third_quad_y(Matrix<int>& map, const Point& origin, double tg) {
  size_t dy = origin.getY() % CELL_SIZE;

  // Point coord for first Y intersection
  double x = origin.getX() - (CELL_SIZE - dy) / tg;
  double y = origin.getY() + (CELL_SIZE - dy);

  double x_step = CELL_SIZE / tg;

  while (true) {
    Point y_intersection(x, y);
    try {
      if (map((int)x, (int)y) >= WALL) {
        return y_intersection;
      }
    } catch (int FIXME) {
      return y_intersection;
    }

    x = x - x_step;
    y = y + CELL_SIZE;
  }
}

Point RayCasting::forth_quad(Matrix<int>& map, Ray& ray) {
  Point origin = ray.get_origin();

  // Precalculate tangent to avoid multiple calls.
  double tg = fabs(tan(ray.get_angle()));

  Point y_intersection = forth_quad_y(map, origin, tg);
  Point x_intersection = forth_quad_x(map, origin, tg);

  double distance1 = Point::distance(ray.get_origin(), x_intersection);
  double distance2 = Point::distance(ray.get_origin(), y_intersection);

  return distance1 < distance2 ? x_intersection : y_intersection;
}

Point forth_quad_x(Matrix<int>& map, const Point& origin, double tg) {
  size_t dx = origin.getX() % CELL_SIZE;

  // Point coord for first X intersection
  double x = origin.getX() + (CELL_SIZE - dx);
  double y = origin.getY() + (CELL_SIZE - dx) * tg;

  double y_step = CELL_SIZE * tg;

  while (true) {
    Point x_intersection(x, y);
    try {
      if (map((int)x, (int)y) >= WALL) {
        return x_intersection;
      }
    } catch (int FIXME) {
      return x_intersection;
    }

    x = x + CELL_SIZE;
    y = y + y_step;
  }
}

Point forth_quad_y(Matrix<int>& map, const Point& origin, double tg) {
  size_t dy = origin.getY() % CELL_SIZE;

  // Point coord for first Y intersection
  double x = origin.getX() + (CELL_SIZE - dy) / tg;
  double y = origin.getY() + (CELL_SIZE - dy);

  double x_step = CELL_SIZE / tg;

  while (true) {
    Point y_intersection(x, y);
    try {
      if (map((int)x, (int)y) >= WALL) {
        return y_intersection;
      }
    } catch (int FIXME) {
      return y_intersection;
    }

    x = x + x_step;
    y = y + CELL_SIZE;
  }
}
