#include "ray_casting.h"

#include <cmath>

#define CELL_SIZE 64
#define MAX_WALL_SIZE 210
#define SIGHT_ANGLE 30
#define WALL 1

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

  return 1 / distance_to_player_sight;

  // TODO Draw from back to front
  // Use similar scaling for sprites
}

Point RayCasting::horizontal_axis(Matrix<int>& map, Ray& ray) {
  printf("HOR: ");
  // Starting point
  size_t x_origin = ray.get_origin().getX();
  size_t y_origin = ray.get_origin().getY();
  double ray_angle = ray.get_angle();

  // Ray offset within the cell
  size_t dx = x_origin % CELL_SIZE;

  Point intersection(-1, -1);

  if (ray_angle == 0) {
    // Point coord for first X intersection
    double x = x_origin + (CELL_SIZE - dx);
    double y = y_origin;

    // FIXME Ask whether to attempt to optimize
    while (true) {
      try {
        if (map((int)x, (int)y) >= WALL) {
          intersection = Point(x, y);
        }
      } catch (int FIXME) {
        break;
      }

      x = x + CELL_SIZE;
    }
  } else {
    // Point coord for first X intersection
    double x = x_origin - dx - 1;
    double y = y_origin;

    while (true) {
      try {
        if (map((int)x, (int)y) >= WALL) {
          intersection = Point(x, y);
        }
      } catch (int FIXME) {
        break;
      }

      x = x - CELL_SIZE;
    }
  }
  printf("HOR: (%d, %d)\n", intersection.getX(), intersection.getY());
  return intersection;
}

Point RayCasting::vertical_axis(Matrix<int>& map, Ray& ray) {
  // Starting point
  size_t x_origin = ray.get_origin().getX();
  size_t y_origin = ray.get_origin().getY();
  double ray_angle = ray.get_angle();

  // Ray offset within the cell
  size_t dy = y_origin % CELL_SIZE;

  if (ray_angle == M_PI_2) {
    // Point coord for first Y intersection
    double x = x_origin;
    double y = y_origin - dy - 1;

    // FIXME Ask whether to attempt to optimize
    while (true) {
      if (map((int)x, (int)y) >= WALL) {
        return Point(x, y);
      }

      y = y - CELL_SIZE;
    }
  } else {
    // Point coord for first X intersection
    double x = x_origin;
    double y = y_origin + (CELL_SIZE - dy);

    while (true) {
      if (map((int)x, (int)y) >= WALL) {
        return Point(x, y);
      }

      y = y + CELL_SIZE;
    }
  }
}

Point RayCasting::first_quad(Matrix<int>& map, Ray& ray) {
  // Starting point
  // printf("Q1 ");
  size_t x_origin = ray.get_origin().getX();
  size_t y_origin = ray.get_origin().getY();
  double ray_angle = ray.get_angle();

  // Ray offset within the cell
  size_t dx = x_origin % CELL_SIZE;
  size_t dy = y_origin % CELL_SIZE;

  // Precalculate tangent
  double tg = fabs(tan(ray_angle));

  // Steps between intersections
  double x_step = CELL_SIZE / tg;
  double y_step = CELL_SIZE * tg;

  // Points of intersection
  Point x_intersection(-1, -1);
  Point y_intersection(-1, -1);

  // Point coord for first Y intersection
  double x = x_origin + dy / tg;
  double y = y_origin - dy - 1;

  // printf("\n");
  while (true) {
    y_intersection = Point(x, y);
    try {
      if (map((int)x, (int)y) >= WALL) {
        break;
      }
    } catch (int a) {
      break;
    }

    x = x + x_step;
    y = y - CELL_SIZE;
  }

  // Point coord for first X intersection
  x = x_origin + (CELL_SIZE - dx);
  y = y_origin - (CELL_SIZE - dx) * tg;

  // printf("\n");
  while (true) {
    x_intersection = Point(x, y);
    try {
      if (map((int)x, (int)y) >= WALL) {
        break;
      }
    } catch (int a) {
      break;
    }

    x = x + CELL_SIZE;
    y = y - y_step;
  }

  double distance1 = Point::distance(ray.get_origin(), x_intersection);
  double distance2 = Point::distance(ray.get_origin(), y_intersection);
  /* TODO ERASE
  if (ray_angle < 0.001) {
    printf("\nANGLE: %f\n", ray_angle);
    printf("P_POS: (%ld, %ld)\n", x_origin, y_origin);
    printf("X_INT: (%d, %d)\n", x_intersection.getX(), x_intersection.getY());
    printf("Y_INT: (%d, %d)\n", y_intersection.getX(), y_intersection.getY());
    printf("D1 %f\n", distance1);
    printf("D2 %f\n", distance2);

    printf("\nDistance Calculation: \n");
    Point point1 = ray.get_origin();
    Point point2 = y_intersection;
    unsigned long term1 = ((long)(point2.getX() - point1.getX())) *
                          ((long)(point2.getX() - point1.getX()));
    unsigned long term2 =
        (point1.getY() - point2.getY()) * (point1.getY() - point2.getY());
    double result = sqrt(term1 + term2);
    printf("POINT1: (%d, %d)\n", x_origin, y_origin);
    printf("POINT2: (%d, %d)\n", y_intersection.getX(), y_intersection.getY());
    printf("Px1 - Px2: %d\n", point1.getX() - point2.getX());
    printf("TERM1: %d\n", term1);
    printf("TERM2: %d\n", term2);
    printf("SQRT: %f\n", result);
  }*/
  if (distance1 < distance2) {
    // printf("X ");
    return x_intersection;
  } else {
    // printf("Y ");
    return y_intersection;
  }
}

Point RayCasting::second_quad(Matrix<int>& map, Ray& ray) {
  // printf("Q2 ");
  // Starting point
  size_t x_origin = ray.get_origin().getX();
  size_t y_origin = ray.get_origin().getY();
  double ray_angle = ray.get_angle();

  // Ray offset within the cell
  size_t dx = x_origin % CELL_SIZE;
  size_t dy = y_origin % CELL_SIZE;

  // Precalculate tangent
  double tg = fabs(tan(ray_angle));

  // Steps between intersections
  double x_step = CELL_SIZE / tg;
  double y_step = CELL_SIZE * tg;

  // Points of intersection
  Point x_intersection(0, 0);
  Point y_intersection(0, 0);

  // Point coord for first Y intersection
  double x = x_origin - dy / tg;
  double y = y_origin - dy - 1;

  while (true) {
    y_intersection = Point(x, y);
    try {
      if (map((int)x, (int)y) >= WALL) {
        break;
      }
    } catch (int FIXME) {
      break;
    }

    x = x - x_step;
    y = y - CELL_SIZE;
  }
  // Point coord for first X intersection
  x = x_origin - dx - 1;
  y = y_origin - dx * tg;

  while (true) {
    x_intersection = Point(x, y);
    try {
      if (map((int)x, (int)y) >= WALL) {
        break;
      }
    } catch (int FIXME) {
      break;
    }

    x = x - CELL_SIZE;
    y = y - y_step;
  }

  double distance1 = Point::distance(ray.get_origin(), x_intersection);
  double distance2 = Point::distance(ray.get_origin(), y_intersection);
  if (distance1 < distance2) {
    return x_intersection;
  } else {
    return y_intersection;
  }
}

Point RayCasting::third_quad(Matrix<int>& map, Ray& ray) {
  // printf("Q3 ");
  size_t x_origin = ray.get_origin().getX();
  size_t y_origin = ray.get_origin().getY();
  double ray_angle = ray.get_angle();

  size_t dx = x_origin % CELL_SIZE;
  size_t dy = y_origin % CELL_SIZE;

  // Precalculate tangent
  double tg = fabs(tan(ray_angle));

  // Steps between intersections
  double x_step = CELL_SIZE / tg;
  double y_step = CELL_SIZE * tg;

  // Points of intersection
  Point x_intersection(0, 0);
  Point y_intersection(0, 0);

  // Point coord for first Y intersection
  double x = x_origin - (CELL_SIZE - dy) / tg;
  double y = y_origin + (CELL_SIZE - dy);

  while (true) {
    y_intersection = Point(x, y);
    try {
      if (map((int)x, (int)y) >= WALL) {
        break;
      }
    } catch (int FIXME) {
      break;
    }

    x = x - x_step;
    y = y + CELL_SIZE;
  }

  // Point coord for first X intersection
  x = x_origin - dx - 1;
  y = y_origin + dx * tg;

  while (true) {
    x_intersection = Point(x, y);
    try {
      if (map((int)x, (int)y) >= WALL) {
        break;
      }
    } catch (int FIXME) {
      break;
    }

    x = x - CELL_SIZE;
    y = y + y_step;
  }

  double distance1 = Point::distance(ray.get_origin(), x_intersection);
  double distance2 = Point::distance(ray.get_origin(), y_intersection);
  if (distance1 < distance2) {
    return x_intersection;
  } else {
    return y_intersection;
  }
}

Point RayCasting::forth_quad(Matrix<int>& map, Ray& ray) {
  // printf("Q4 ");
  size_t x_origin = ray.get_origin().getX();
  size_t y_origin = ray.get_origin().getY();
  double ray_angle = ray.get_angle();

  size_t dx = x_origin % CELL_SIZE;
  size_t dy = y_origin % CELL_SIZE;

  // Precalculate tangent
  double tg = fabs(tan(ray_angle));

  // Step between intersections
  double x_step = CELL_SIZE / tg;
  double y_step = CELL_SIZE * tg;

  // Points of intersection
  Point x_intersection(0, 0);
  Point y_intersection(0, 0);

  // Point coord for first Y intersection
  double x = x_origin + (CELL_SIZE - dy) / tg;
  double y = y_origin + (CELL_SIZE - dy);

  while (true) {
    y_intersection = Point(x, y);
    try {
      if (map((int)x, (int)y) >= WALL) {
        break;
      }
    } catch (int FIXME) {
      break;
    }

    x = x + x_step;
    y = y + CELL_SIZE;
  }

  // Point coord for first X intersection
  x = x_origin + (CELL_SIZE - dx);
  y = y_origin + (CELL_SIZE - dx) * tg;

  while (true) {
    x_intersection = Point(x, y);
    try {
      if (map((int)x, (int)y) >= WALL) {
        break;
      }
    } catch (int FIXME) {
      break;
    }

    x = x + CELL_SIZE;
    y = y + y_step;
  }

  double distance1 = Point::distance(ray.get_origin(), x_intersection);
  double distance2 = Point::distance(ray.get_origin(), y_intersection);
  // printf("\nANGLE: %f\n", ray_angle);
  // printf("X_INT: (%d, %d)\n", x_intersection.getX(), x_intersection.getY());
  // printf("Y_INT: (%d, %d)\n", y_intersection.getX(), y_intersection.getY());
  if (distance1 < distance2) {
    return x_intersection;
  } else {
    return y_intersection;
  }
}