#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>

using namespace sf; 
using namespace std;

const double L = 260;
const double L1 = 5;
const double alpha1 = 4;
const double alpha2 = 4;
const double M = 1;

class Vector {
public:
    double x;
    double y;
    double z;
    Vector() {}
    Vector(double x1, double y1, double z1) {
        x = x1;
        y = y1;
        z = z1;
    }
    friend double len(Vector a) {
        return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
    }
    friend Vector sub(Vector a, Vector b) {
        return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
    }
    friend Vector add(Vector a, Vector b) {
        return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
    }
    friend Vector mul(Vector a, double c) {
        return Vector(a.x * c, a.y * c, a.z * c);
    }
};

class Particle {
public:
    Vector r;
    Vector v;
    double m;
    Particle() {}
    Particle(Vector r1, Vector v1) {
        r = r1;
        v = v1;
        m = M;
    }
    double pot_en(Particle p1, Particle p2) {
        double dr = len(sub(p1.r, p2.r));
        return (alpha1 / pow(dr, 12) - alpha2 / pow(dr, 6));
    }
    double kin_en(Particle p) {
        return (p.m * pow(len(p.v), 2) / 2);
    }
    friend Particle nearest(Particle p1, Particle p2) {
        while ((p2.r.x - p1.r.x) > L / 2) {
            p2.r.x -= L;
        }
        while ((p2.r.x - p1.r.x) < -(L / 2)) {
            p2.r.x += L;
        }
        while ((p2.r.y - p1.r.y) > L / 2) {
            p2.r.y -= L;
        }
        while ((p2.r.y - p1.r.y) < -(L / 2)) {
            p2.r.y += L;
        }
        while ((p2.r.z - p1.r.z) > L / 2) {
            p2.r.z -= L;
        }
        while ((p2.r.z - p1.r.z) < -(L / 2)) {
            p2.r.z += L;
        }
        return p2;
    }

    friend Vector force(Particle* arr, int x, int n) {
        Vector force_sum = Vector(0, 0, 0);
        for (int i = 0; i < n; i++) {
            if (i != x) {
                Vector drmin = sub(arr[x].r, nearest(arr[x], arr[i]).r);
                double force_abs = 6 * (alpha2 / pow(len(drmin), 7) - (2 * alpha1) / pow(len(drmin), 13));
                force_sum = add(force_sum, mul(drmin, -(force_abs / len(drmin))));
            }
        }
        return force_sum;
    }
};

void ch_coord(Particle* arr, int n, double dt) {
    Particle* new_p = new Particle[n];
    Vector f;
    for (int i = 0; i < n; i++) {
        f = force(arr, i, n);
        new_p[i].v = add(arr[i].v, mul(f, (dt / (2 * arr[i].m))));
        new_p[i].r = add(arr[i].r, mul(new_p[i].v, dt));
        new_p[i].m = M;
    }
    for (int i = 0; i < n; i++) {
        f = force(new_p, i, n);
        new_p[i].v = add(new_p[i].v, mul(f, (dt / (2 * arr[i].m))));
    }
    for (int i = 0; i < n; i++) {
        if ((new_p[i].r.x > L) || (new_p[i].r.x < 0)) {
            new_p[i].r.x = abs(new_p[i].r.x - L);
        }
        if ((new_p[i].r.y > L) || (new_p[i].r.y < 0)) {
            new_p[i].r.y = abs(new_p[i].r.y - L);
        }
        if ((new_p[i].r.z > L) || (new_p[i].r.z < 0)) {
            new_p[i].r.z = abs(new_p[i].r.z - L);
        }
    }
    for (int i = 0; i < n; i++) {
        arr[i] = new_p[i];
    }
    delete[] new_p;
}

int main()
{
    int n = 3;
    int particles_cnt = n * n * n;
    double coords_coef = (L - 2*L1) / (n - 1);
    double dt = 1e-3;
    mt19937_64 rng(0);
    uniform_real_distribution<> rand(-0.5, 0.5);
    Particle* arr = new Particle[particles_cnt];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                arr[i + n * j + n * n * k].r = Vector(i * coords_coef + L1, j * coords_coef + L1, k * coords_coef + L1);
                double vx = rand(rng)*20;
                double vy = rand(rng)*20;
                double vz = rand(rng)*20;
                arr[i + n * j + n * n * k].v = Vector(vx, vy, vz);
                arr[i + n * j + n * n * k].m = M;
            }
        }
    }
	RenderWindow window(VideoMode(800, 800), "Project");           
	while (window.isOpen())
    {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) 
				window.close();
		}

		window.clear(Color(176, 196, 222));

        double X = 50;
        double Y = 50;
        double width = 300; 
        double heigth = 300;
        double R = 15;
        double d = 20; 

        ConvexShape convex1;
        convex1.setPointCount(4);
        convex1.setPoint(0, Vector2f(X, Y));
        convex1.setPoint(1, Vector2f(X + width, Y));
        convex1.setPoint(2, Vector2f(X + width, Y + heigth));
        convex1.setPoint(3, Vector2f(X, Y + heigth));
        convex1.setFillColor(Color::White);
        window.draw(convex1);

        ConvexShape axe1;
        axe1.setPointCount(4);
        axe1.setPoint(0, Vector2f(X - 2, Y - 2));
        axe1.setPoint(1, Vector2f(X + width + 2, Y - 2));
        axe1.setPoint(2, Vector2f(X + width + 2, Y + 2));
        axe1.setPoint(3, Vector2f(X - 2, Y + 2));
        axe1.setFillColor(Color::Black);
        window.draw(axe1);

        ConvexShape tr1;
        tr1.setPointCount(3);
        tr1.setPoint(0, Vector2f(X + width + 2, Y - 10));
        tr1.setPoint(1, Vector2f(X + width + 10, Y));
        tr1.setPoint(2, Vector2f(X + width + 2, Y + 10));
        tr1.setFillColor(Color::Black);
        window.draw(tr1);

        ConvexShape axe2;
        axe2.setPointCount(4);
        axe2.setPoint(0, Vector2f(X - 2, Y - 2));
        axe2.setPoint(1, Vector2f(X + 2, Y - 2));
        axe2.setPoint(2, Vector2f(X + 2, Y + heigth + 2));
        axe2.setPoint(3, Vector2f(X - 2, Y + heigth + 2));
        axe2.setFillColor(Color::Black);
        window.draw(axe2);

        ConvexShape tr2;
        tr2.setPointCount(3);
        tr2.setPoint(0, Vector2f(X + 10, Y + heigth + 2));
        tr2.setPoint(1, Vector2f(X, Y + heigth + 10));
        tr2.setPoint(2, Vector2f(X - 10, Y + heigth + 2));
        tr2.setFillColor(Color::Black);
        window.draw(tr2);

        for (int i = 0; i < particles_cnt; i++) {
            CircleShape particle(R);
            particle.setPosition(arr[i].r.x + X + d - R, arr[i].r.y + Y + d - R);
            particle.setFillColor(Color::Black);
            window.draw(particle);
        }

        X = 400;
        Y = 50;
        ConvexShape convex2;
        convex2.setPointCount(4);
        convex2.setPoint(0, Vector2f(X, Y));
        convex2.setPoint(1, Vector2f(X + width, Y));
        convex2.setPoint(2, Vector2f(X + width, Y + heigth));
        convex2.setPoint(3, Vector2f(X, Y + heigth));
        convex2.setFillColor(Color::White);
        window.draw(convex2);

        ConvexShape axe3;
        axe3.setPointCount(4);
        axe3.setPoint(0, Vector2f(X - 2, Y - 2));
        axe3.setPoint(1, Vector2f(X + width + 2, Y - 2));
        axe3.setPoint(2, Vector2f(X + width + 2, Y + 2));
        axe3.setPoint(3, Vector2f(X - 2, Y + 2));
        axe3.setFillColor(Color::Black);
        window.draw(axe3);

        ConvexShape tr3;
        tr3.setPointCount(3);
        tr3.setPoint(0, Vector2f(X + width + 2, Y - 10));
        tr3.setPoint(1, Vector2f(X + width + 10, Y));
        tr3.setPoint(2, Vector2f(X + width + 2, Y + 10));
        tr3.setFillColor(Color::Black);
        window.draw(tr3);

        ConvexShape axe4;
        axe4.setPointCount(4);
        axe4.setPoint(0, Vector2f(X - 2, Y - 2));
        axe4.setPoint(1, Vector2f(X + 2, Y - 2));
        axe4.setPoint(2, Vector2f(X + 2, Y + heigth + 2));
        axe4.setPoint(3, Vector2f(X - 2, Y + heigth + 2));
        axe4.setFillColor(Color::Black);
        window.draw(axe4);

        ConvexShape tr4;
        tr4.setPointCount(3);
        tr4.setPoint(0, Vector2f(X + 10, Y + heigth + 2));
        tr4.setPoint(1, Vector2f(X, Y + heigth + 10));
        tr4.setPoint(2, Vector2f(X - 10, Y + heigth + 2));
        tr4.setFillColor(Color::Black);
        window.draw(tr4);

        for (int i = 0; i < particles_cnt; i++) {
            CircleShape particle(R);
            particle.setPosition(arr[i].r.y + X + d - R, arr[i].r.z + Y + d - R);
            particle.setFillColor(Color::Black);
            window.draw(particle);
        }

        X = 50;
        Y = 400;
        ConvexShape convex3;
        convex3.setPointCount(4);
        convex3.setPoint(0, Vector2f(X, Y));
        convex3.setPoint(1, Vector2f(X + width, Y));
        convex3.setPoint(2, Vector2f(X + width, Y + heigth));
        convex3.setPoint(3, Vector2f(X, Y + heigth));
        convex3.setFillColor(Color::White);
        window.draw(convex3);

        ConvexShape axe5;
        axe5.setPointCount(4);
        axe5.setPoint(0, Vector2f(X - 2, Y - 2));
        axe5.setPoint(1, Vector2f(X + width + 2, Y - 2));
        axe5.setPoint(2, Vector2f(X + width + 2, Y + 2));
        axe5.setPoint(3, Vector2f(X - 2, Y + 2));
        axe5.setFillColor(Color::Black);
        window.draw(axe5);

        ConvexShape tr5;
        tr5.setPointCount(3);
        tr5.setPoint(0, Vector2f(X + width + 2, Y - 10));
        tr5.setPoint(1, Vector2f(X + width + 10, Y));
        tr5.setPoint(2, Vector2f(X + width + 2, Y + 10));
        tr5.setFillColor(Color::Black);
        window.draw(tr5);

        ConvexShape axe6;
        axe6.setPointCount(4);
        axe6.setPoint(0, Vector2f(X - 2, Y - 2));
        axe6.setPoint(1, Vector2f(X + 2, Y - 2));
        axe6.setPoint(2, Vector2f(X + 2, Y + heigth + 2));
        axe6.setPoint(3, Vector2f(X - 2, Y + heigth + 2));
        axe6.setFillColor(Color::Black);
        window.draw(axe6);

        ConvexShape tr6;
        tr6.setPointCount(3);
        tr6.setPoint(0, Vector2f(X + 10, Y + heigth + 2));
        tr6.setPoint(1, Vector2f(X, Y + heigth + 10));
        tr6.setPoint(2, Vector2f(X - 10, Y + heigth + 2));
        tr6.setFillColor(Color::Black);
        window.draw(tr6);

        for (int i = 0; i < particles_cnt; i++) {
            CircleShape particle(R);
            particle.setPosition(arr[i].r.x + X + d - R, arr[i].r.z + Y + d - R);
            particle.setFillColor(Color::Black);
            window.draw(particle);
        }

		window.display();
        ch_coord(arr, particles_cnt, dt);
	}

	return 0;
}