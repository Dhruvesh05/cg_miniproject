#include <graphics.h>
#include <iostream>
#include <cmath>

using namespace std;

// Function to draw axes with markings (scale)
void drawAxesWithMarkings() {
    int midX = getmaxx() / 2;
    int midY = getmaxy() / 2;

    // Draw X and Y axes
    line(0, midY, getmaxx(), midY);  // X-axis
    line(midX, 0, midX, getmaxy());  // Y-axis

    // Markings for X-axis
    for (int x = midX; x < getmaxx(); x += 50) {
        line(x, midY - 5, x, midY + 5);  // Positive X tick marks
        if (x != midX) {
            char label[10];
            sprintf(label, "%d", (x - midX) / 50);
            outtextxy(x - 5, midY + 10, label);
        }
    }
    for (int x = midX; x > 0; x -= 50) {
        line(x, midY - 5, x, midY + 5);  // Negative X tick marks
        if (x != midX) {
            char label[10];
            sprintf(label, "%d", -(midX - x) / 50);
            outtextxy(x - 10, midY + 10, label);
        }
    }

    // Markings for Y-axis
    for (int y = midY; y < getmaxy(); y += 50) {
        line(midX - 5, y, midX + 5, y);  // Positive Y tick marks
        if (y != midY) {
            char label[10];
            sprintf(label, "%d", -(y - midY) / 50);
            outtextxy(midX + 10, y - 5, label);
        }
    }
    for (int y = midY; y > 0; y -= 50) {
        line(midX - 5, y, midX + 5, y);  // Negative Y tick marks
        if (y != midY) {
            char label[10];
            sprintf(label, "%d", (midY - y) / 50);
            outtextxy(midX + 10, y - 5, label);
        }
    }
}

// Base class: Graph
class Graph {
public:
    virtual void draw() = 0;  // Pure virtual function for drawing the graph
};

// Derived class: Line for plotting linear functions
class Line : public Graph {
private:
    float slope;
    float intercept;

public:
    Line(float m, float c) : slope(m), intercept(c) {}

    void draw() override {
        int midX = getmaxx() / 2;
        int midY = getmaxy() / 2;

        // Plot y = mx + c
        for (int x = -midX; x < midX; x++) {
            int y = slope * x + intercept;
            putpixel(midX + x, midY - y, WHITE);
        }
    }
};

// Derived class: Parabola
class Parabola : public Graph {
private:
    float a, b, c;

public:
    Parabola(float coefA, float coefB, float coefC) : a(coefA), b(coefB), c(coefC) {}

    void draw() override {
        int midX = getmaxx() / 2;
        int midY = getmaxy() / 2;

        // Plot y = ax^2 + bx + c
        for (int x = -midX; x < midX; x++) {
            int y = a * x * x + b * x + c;
            putpixel(midX + x, midY - y, WHITE);
        }
    }
};

// Derived class: Ellipse
class EllipseGraph : public Graph {
private:
    int a, b;

public:
    EllipseGraph(int semiMajor, int semiMinor) : a(semiMajor), b(semiMinor) {}

    void draw() override {
        int midX = getmaxx() / 2;
        int midY = getmaxy() / 2;

        // Draw the ellipse
        ellipse(midX, midY, 0, 360, a, b);
    }
};

// Derived class: Hyperbola
class Hyperbola : public Graph {
private:
    float a, b;

public:
    Hyperbola(float semiMajor, float semiMinor) : a(semiMajor), b(semiMinor) {}

    void draw() override {
        int midX = getmaxx() / 2;
        int midY = getmaxy() / 2;

        // Plot hyperbola y^2/b^2 - x^2/a^2 = 1
        for (int x = -midX; x < midX; x++) {
            if ((x * x / (a * a)) <= 1) continue;
            int y1 = sqrt((x * x * b * b / (a * a)) + b * b);
            int y2 = -sqrt((x * x * b * b / (a * a)) + b * b);
            putpixel(midX + x, midY - y1, WHITE);
            putpixel(midX + x, midY - y2, WHITE);
        }
    }
};

// Derived class: Trigonometric (Sine and Cosine)
class Trigonometric : public Graph {
private:
    bool isSine;

public:
    Trigonometric(bool sine) : isSine(sine) {}

    void draw() override {
        int midX = getmaxx() / 2;
        int midY = getmaxy() / 2;

        // Plot sine or cosine
        for (int x = -midX; x < midX; x++) {
            float rad = x * 0.05;  // Scale factor for plotting
            int y = isSine ? sin(rad) * 100 : cos(rad) * 100;
            putpixel(midX + x, midY - y, WHITE);
        }
    }
};

// Derived class: Logarithmic
class Logarithmic : public Graph {
public:
    void draw() override {
        int midX = getmaxx() / 2;
        int midY = getmaxy() / 2;

        // Plot y = log(x)
        for (int x = 1; x < midX; x++) {  // Starting from x = 1 to avoid log(0)
            int y = log(x) * 50;  // Scale factor for plotting
            putpixel(midX + x, midY - y, WHITE);
        }
    }
};

// Utility class: GraphPlotter
class GraphPlotter {
public:
    void plot(Graph* graph) {
        drawAxesWithMarkings();  // Draw the axes with markings first
        graph->draw();  // Then plot the graph on top of the axes
    }
};

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int choice;
    cout << "Graph Plotter\n";
    cout << "1. Plot Line (y = mx + c)\n";
    cout << "2. Plot Parabola (y = ax^2 + bx + c)\n";
    cout << "3. Plot Ellipse\n";
    cout << "4. Plot Hyperbola\n";
    cout << "5. Plot Sine\n";
    cout << "6. Plot Cosine\n";
    cout << "7. Plot Logarithmic\n";
    cout << "Enter your choice: ";
    cin >> choice;

    GraphPlotter plotter;
    if (choice == 1) {
        float m, c;
        cout << "Enter slope (m): ";
        cin >> m;
        cout << "Enter y-intercept (c): ";
        cin >> c;

        Line line(m, c);
        plotter.plot(&line);
    } else if (choice == 2) {
        float a, b, c;
        cout << "Enter coefficient a: ";
        cin >> a;
        cout << "Enter coefficient b: ";
        cin >> b;
        cout << "Enter coefficient c: ";
        cin >> c;

        Parabola parabola(a, b, c);
        plotter.plot(&parabola);
    } else if (choice == 3) {
        int a, b;
        cout << "Enter semi-major axis (a): ";
        cin >> a;
        cout << "Enter semi-minor axis (b): ";
        cin >> b;

        EllipseGraph ellipse(a, b);
        plotter.plot(&ellipse);
    } else if (choice == 4) {
        float a, b;
        cout << "Enter semi-major axis (a): ";
        cin >> a;
        cout << "Enter semi-minor axis (b): ";
        cin >> b;

        Hyperbola hyperbola(a, b);
        plotter.plot(&hyperbola);
    } else if (choice == 5) {
        Trigonometric sine(true);
        plotter.plot(&sine);
    } else if (choice == 6) {
        Trigonometric cosine(false);
        plotter.plot(&cosine);
    } else if (choice == 7) {
        Logarithmic logGraph;
        plotter.plot(&logGraph);
    }

    getch();
    closegraph();
    return 0;
}