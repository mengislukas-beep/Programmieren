#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std;
void clearScreen() {
    cout << "\x1B[2J\x1B[H";
}

void print(const vector<string>& screen) {
    for (const auto& row : screen) {
        cout << row << '\n';
    }
}

struct Vec3 {
    double x, y, z;
};

struct Surface {
    vector<pair<Vec3, char>> points;
};

vector<string> to_string(const Surface& surface, int width = 200, int height = 44) {
    vector<string> result(height, string(width, ' '));

    for (const auto& entry : surface.points) {
        const Vec3& p = entry.first;
        char ch = entry.second;

        int x = static_cast<int>(std::round(p.x));
        int y = static_cast<int>(std::round(p.y/2.5));

        if (x >= 0 && x < width && y >= 0 && y < height) {
            result[y][x] = ch;
        }
    }

    return result;
}

Vec3 rotatePoint(Vec3 p, double alpha, double beta, double gamma) {
    // Rotation um x-Achse
    double y1 = p.y * cos(alpha) - p.z * sin(alpha);
    double z1 = p.y * sin(alpha) + p.z * cos(alpha);
    p.y = y1;
    p.z = z1;

    // Rotation um y-Achse
    double x2 = p.x * cos(beta) + p.z * sin(beta);
    double z2 = -p.x * sin(beta) + p.z * cos(beta);
    p.x = x2;
    p.z = z2;

    // Rotation um z-Achse
    double x3 = p.x * cos(gamma) - p.y * sin(gamma);
    double y3 = p.x * sin(gamma) + p.y * cos(gamma);
    p.x = x3;
    p.y = y3;

    return p;
}

Surface rotateSurface(const Surface& s, double alpha, double beta, double gamma) {
    Surface result;

    for (const auto& entry : s.points) {
        Vec3 rotated = rotatePoint(entry.first, alpha, beta, gamma);
        result.points.push_back({rotated, entry.second});
    }

    return result;
}

namespace {
    constexpr double EPS = 1e-9;

    double cross2d(double ax, double ay, double bx, double by) {
        return ax * by - ay * bx;
    }

    double orient2d(const Vec3& a, const Vec3& b, double px, double py) {
        return cross2d(b.x - a.x, b.y - a.y, px - a.x, py - a.y);
    }

    bool point_in_triangle_inclusive(
        double px, double py,
        const Vec3& a, const Vec3& b, const Vec3& c)
    {
        double c1 = orient2d(a, b, px, py);
        double c2 = orient2d(b, c, px, py);
        double c3 = orient2d(c, a, px, py);

        bool has_neg = (c1 < -EPS) || (c2 < -EPS) || (c3 < -EPS);
        bool has_pos = (c1 > EPS) || (c2 > EPS) || (c3 > EPS);

        return !(has_neg && has_pos);
    }

    bool barycentric_2d(
        double px, double py,
        const Vec3& a, const Vec3& b, const Vec3& c,
        double& w0, double& w1, double& w2)
    {
        double denom =
            (b.y - c.y) * (a.x - c.x) +
            (c.x - b.x) * (a.y - c.y);

        if (std::abs(denom) < EPS) {
            return false;
        }

        w0 = ((b.y - c.y) * (px - c.x) + (c.x - b.x) * (py - c.y)) / denom;
        w1 = ((c.y - a.y) * (px - c.x) + (a.x - c.x) * (py - c.y)) / denom;
        w2 = 1.0 - w0 - w1;
        return true;
    }
}

Surface make_surface(const Surface& triangle, Surface& already) {
    Surface result;

    if (triangle.points.size() < 3) {
        return result;
    }

    const Vec3& a = triangle.points[0].first;
    const Vec3& b = triangle.points[1].first;
    const Vec3& c = triangle.points[2].first;

    char draw_char = triangle.points[0].second;
    if (!triangle.points.empty()) {
        draw_char = triangle.points[0].second;
    }

    int min_x = static_cast<int>(std::ceil(std::min({a.x, b.x, c.x})));
    int max_x = static_cast<int>(std::floor(std::max({a.x, b.x, c.x})));
    int min_y = static_cast<int>(std::ceil(std::min({a.y, b.y, c.y})));
    int max_y = static_cast<int>(std::floor(std::max({a.y, b.y, c.y})));

    for (int y = min_y; y <= max_y; ++y) {
        for (int x = min_x; x <= max_x; ++x) {
            double px = static_cast<double>(x);
            double py = static_cast<double>(y);

            if (!point_in_triangle_inclusive(px, py, a, b, c)) {
                continue;
            }

            double w0, w1, w2;
            if (!barycentric_2d(px, py, a, b, c, w0, w1, w2)) {
                continue;
            }

            double z = w0 * a.z + w1 * b.z + w2 * c.z;
            Vec3 p{px, py, z};

            result.points.push_back({p, draw_char});
        }
    }

    return result;
}

Surface make_cube(const string& sign, int x, int y, int z, int size) {
    char ch = sign.empty() ? '#' : sign[0];

    Vec3 p000 = {double(x),        double(y),        double(z)};
    Vec3 p100 = {double(x + size), double(y),        double(z)};
    Vec3 p010 = {double(x),        double(y + size), double(z)};
    Vec3 p110 = {double(x + size), double(y + size), double(z)};

    Vec3 p001 = {double(x),        double(y),        double(z + size)};
    Vec3 p101 = {double(x + size), double(y),        double(z + size)};
    Vec3 p011 = {double(x),        double(y + size), double(z + size)};
    Vec3 p111 = {double(x + size), double(y + size), double(z + size)};

    Surface s1  = { { {p000, ch}, {p100, ch}, {p110, ch} } };
    Surface s2  = { { {p000, ch}, {p110, ch}, {p010, ch} } };

    Surface s3  = { { {p001, ch}, {p111, ch}, {p101, ch} } };
    Surface s4  = { { {p001, ch}, {p011, ch}, {p111, ch} } };

    Surface s5  = { { {p000, ch}, {p010, ch}, {p011, ch} } };
    Surface s6  = { { {p000, ch}, {p011, ch}, {p001, ch} } };

    Surface s7  = { { {p100, ch}, {p101, ch}, {p111, ch} } };
    Surface s8  = { { {p100, ch}, {p111, ch}, {p110, ch} } };

    Surface s9  = { { {p010, ch}, {p110, ch}, {p111, ch} } };
    Surface s10 = { { {p010, ch}, {p111, ch}, {p011, ch} } };

    Surface s11 = { { {p000, ch}, {p001, ch}, {p101, ch} } };
    Surface s12 = { { {p000, ch}, {p101, ch}, {p100, ch} } };

    Surface result;

    result = make_surface(s1, result);
    Surface tmp;

    tmp = make_surface(s2, result);
    result.points.insert(result.points.end(), tmp.points.begin(), tmp.points.end());

    tmp = make_surface(s3, result);
    result.points.insert(result.points.end(), tmp.points.begin(), tmp.points.end());

    tmp = make_surface(s4, result);
    result.points.insert(result.points.end(), tmp.points.begin(), tmp.points.end());

    tmp = make_surface(s5, result);
    result.points.insert(result.points.end(), tmp.points.begin(), tmp.points.end());

    tmp = make_surface(s6, result);
    result.points.insert(result.points.end(), tmp.points.begin(), tmp.points.end());

    tmp = make_surface(s7, result);
    result.points.insert(result.points.end(), tmp.points.begin(), tmp.points.end());

    tmp = make_surface(s8, result);
    result.points.insert(result.points.end(), tmp.points.begin(), tmp.points.end());

    tmp = make_surface(s9, result);
    result.points.insert(result.points.end(), tmp.points.begin(), tmp.points.end());

    tmp = make_surface(s10, result);
    result.points.insert(result.points.end(), tmp.points.begin(), tmp.points.end());

    tmp = make_surface(s11, result);
    result.points.insert(result.points.end(), tmp.points.begin(), tmp.points.end());

    tmp = make_surface(s12, result);
    result.points.insert(result.points.end(), tmp.points.begin(), tmp.points.end());

    return result;
}

vector<Vec3> cube(int x, int y, int z, int size) {
    
    vector<Vec3> result;
    result.push_back({double(x),        double(y),        double(z)});
    result.push_back({double(x + size), double(y),        double(z)});
    result.push_back({double(x),        double(y + size), double(z)});
    result.push_back({double(x + size), double(y + size), double(z)});

    result.push_back({double(x),        double(y),        double(z + size)});
    result.push_back({double(x + size), double(y),        double(z + size)});
    result.push_back({double(x),        double(y + size), double(z + size)});
    result.push_back({double(x + size), double(y + size), double(z + size)});
    return result;
}