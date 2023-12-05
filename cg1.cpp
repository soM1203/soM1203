#include <iostream>
#include <graphics.h>

class Polygon {
protected:
    int numPoints;
    int *xPoints;
    int *yPoints;

public:
    Polygon(int num, int *x, int *y) : numPoints(num), xPoints(x), yPoints(y) {}

    virtual void draw() {
        for (int i = 0; i < numPoints; ++i) {
            int j = (i + 1) % numPoints;
            line(xPoints[i], yPoints[i], xPoints[j], yPoints[j]);
        }
    }
};

class ConcavePolygon : public Polygon {
private:
    int fillColor;

public:
    ConcavePolygon(int num, int *x, int *y, int color) : Polygon(num, x, y), fillColor(color) {}

    void scanFill() {
        int maxX = -1, maxY = -1, minX = getmaxx() + 1, minY = getmaxy() + 1;
        for (int i = 0; i < numPoints; ++i) {
            if (xPoints[i] > maxX) maxX = xPoints[i];
            if (xPoints[i] < minX) minX = xPoints[i];
            if (yPoints[i] > maxY) maxY = yPoints[i];
            if (yPoints[i] < minY) minY = yPoints[i];
        }

        for (int y = minY; y <= maxY; ++y) {
            for (int x = minX; x <= maxX; ++x) {
                int count = 0;
                for (int i = 0, j = numPoints - 1; i < numPoints; j = i++) {
                    if (((yPoints[i] > y) != (yPoints[j] > y)) &&
                        (x < (xPoints[j] - xPoints[i]) * (y - yPoints[i]) / (yPoints[j] - yPoints[i]) + xPoints[i])) {
                        count++;
                    }
                }
                if (count % 2 == 1) {
                    putpixel(x, y, fillColor);
                }
            }
        }
    }
};

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int pointsX[] = {100, 200, 300, 400};
    int pointsY[] = {100, 150, 300, 200};

    ConcavePolygon concavePolygon(4, pointsX, pointsY, BLUE);
    concavePolygon.draw();
    concavePolygon.scanFill();

    delay(5000);
    closegraph();
    return 0;
}
