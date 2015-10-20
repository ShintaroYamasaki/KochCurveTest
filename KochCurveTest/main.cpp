//
//  main.cpp
//  KochCurveTest
//
//  Created by 山崎 慎太郎 on 2014/12/11.
//  Copyright (c) 2014年 山崎 慎太郎. All rights reserved.
//

#include <iostream>

#include <GLUT/glut.h>
#include "math.h"

/// 円周率
#define PI 3.14159265
/// 画面サイズ
#define WINDOW_SIZE 800

/// 座標
typedef struct {
    /// X座標
    double x;
    /// Y座標
    double y;
} Point;

/// ウィンドウタイトル
char title[] = "Koch Curve";

/// 世代数
int count = 0;
/// 線の端
Point a = {-1.0, -0.3};
Point b = {1.0, -0.3};

/// コッホ曲線描画
void drawKochCurve(Point a, Point b, int n) {
    // 新たな頂点
    Point c, d, e;
    
    double nx, ny, agl1, agl2, dist;
    
    c.x = (2 * a.x + b.x) / 3.0;
    c.y = (2 * a.y + b.y) / 3.0;
    d.x = (a.x + 2 * b.x) / 3.0;
    d.y = (a.y + 2 * b.y) / 3.0;
    nx = b.x - a.x;
    ny = -(b.y - a.y);
    
    dist = sqrt(nx * nx + ny * ny) / sqrt(3.0);
    

    
    // 直線が右上がり
    if (nx >= 0) {
        agl1 = atan(ny / nx) - PI / 6.0;
        e.x = a.x + (dist * cos(agl1));
        e.y = a.y - (dist * sin(agl1));
    }
    // 直線が右下がり
    else {
        agl2 = atan(ny / nx) + PI / 6.0;
        e.x = b.x + (dist * cos(agl2));
        e.y = b.y - (dist * sin(agl2));
    }
    
    // 頂点を設定
    if (n <= 0) {
        glBegin(GL_LINE_STRIP);
        glColor4d(1.0, 1.0, 1.0, 1.0);
            glVertex2f(a.x, a.y);
            glVertex2f(c.x, c.y);
            glVertex2f(e.x, e.y);
            glVertex2f(d.x, d.y);
            glVertex2f(b.x, b.y);
        glEnd();
    }
    // 再起
    else {
        drawKochCurve(a, c, n - 1);
        drawKochCurve(c, e, n - 1);
        drawKochCurve(e, d, n - 1);
        drawKochCurve(d, b, n - 1);
    }
}

void drawMountain(Point a, Point b, int n) {
    // 新たな頂点
    Point c, d, e, f;
    
    c.x = (2 * a.x + b.x) / 3.0;
    c.y = (2 * a.y + b.y) / 3.0;
    d.x = (a.x + 2 * b.x) / 3.0;
    d.y = (a.y + 2 * b.y) / 3.0;
    
    double lx, ly;
    lx = b.x - a.x;
    ly = b.y - a.y;
    
    /// a, b間の長さ
    double dist = sqrt(lx * lx + ly * ly);
    
    /// 台形斜辺の長さ
    double sdist = dist / 3.0 * 0.5;
    
    /// 斜辺角度
    double agl;
    
    if (lx >= 0) {
        agl = atan(ly / lx) + PI / 3.0;
        e.x = c.x + sdist * cos(agl);
        e.y = c.y + sdist * sin(agl);
        agl = atan(ly / lx) + (PI - PI / 3.0);
        f.x = d.x + sdist * cos(agl);
        f.y = d.y + sdist * sin(agl);
    } else {
        agl = atan(ly / lx) + PI / 3.0;
        e.x = c.x - sdist * cos(agl);
        e.y = c.y - sdist * sin(agl);
        agl = atan(ly / lx) + (PI - PI / 3.0);
        f.x = d.x - sdist * cos(agl);
        f.y = d.y - sdist * sin(agl);
    }
    
    
    // 頂点を設定
    if (n <= 0) {
        glBegin(GL_LINE_STRIP);
        glColor4d(1.0, 1.0, 1.0, 1.0);
        glVertex2f(a.x, a.y);
        glVertex2f(c.x, c.y);
        glVertex2f(e.x, e.y);
        glVertex2d(f.x, f.y);
        glVertex2f(d.x, d.y);
        glVertex2f(b.x, b.y);
        glEnd();
    }
    // 再起
    else {
        drawMountain(a, c, n - 1);
        drawMountain(c, e, n - 1);
        drawMountain(e, f, n - 1);
        drawMountain(f, d, n - 1);
        drawMountain(d, b, n - 1);
    }

}

/// リセット
void reset() {
    count = 0;
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLineWidth(1.0);
    glBegin(GL_LINES);
    glColor4d(1.0, 1.0, 1.0, 1.0);
    glVertex2d(a.x, a.y);
    glVertex2d(b.x, b.y);
    glEnd();
    
    glFlush();
}

/// コールバック関数
void disp(void) {
    
    reset();
    
}

/// キーアクション
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case ' ': {
            glClearColor(0.0, 0.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            // コッホ曲線描画
//            drawKochCurve(a, b, count);
            drawMountain(a, b, count);
            
            glFlush();

            count++;
            break;
        }
        case 'r':
            reset();
            
            break;
        default:
            break;
    }
}


int main(int argc , char ** argv) {
    glutInit(&argc , argv);
    glutInitWindowPosition(100 , 50);
    glutInitWindowSize(WINDOW_SIZE , WINDOW_SIZE);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    
    glutCreateWindow(title);
    glutDisplayFunc(disp);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}