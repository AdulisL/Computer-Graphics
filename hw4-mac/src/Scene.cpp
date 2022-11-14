#include "Scene.h"

// Default parameters
int Scene::height = 800;
int Scene::width = 800;
int Scene::oldx = 0;
int Scene::oldy = 0;
int Scene::resolution = 30;
int Scene::subdivLevel = 1;
int Scene::mode = 0;
ControlCurve *Scene::control = new ControlCurve();
Curve *Scene::curve = new Curve();
CurveShader *Scene::shader = new CurveShader;

Scene::Scene()
{
}
void Scene::init()
{
    shader->read_source("shaders/simple.vert", "shaders/curve.frag");
    shader->compile();
    glUseProgram(shader->program);
    shader->initUniforms();
}
void Scene::printHelp()
{
    std::cout << R"(
    Available commands:
      press 'h' to print this message again.
      press Esc to quit.
      press '+' and '-' to increase/decrease curve resolution.
      press 'a' and 'z' to increase/decrease subdivision level.
      press '0' : Show control polygon only
      press '1' : Show Bezier curve
      press '2' : Show B-spline
      press '3' : Show subdivision curve
      press 'r' : Reset control polygon
)";
}
void Scene::keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '0':
        mode = 0;
        std::cout << "Mode 0: Straight line." << std::endl;
        break;
    case '1':
        mode = 1;
        std::cout << "Mode 1: Bezier curve." << std::endl;
        break;
    case '2':
        mode = 2;
        std::cout << "Mode 2: B-spline curve." << std::endl;
        break;
    case '3':
        mode = 3;
        std::cout << "Mode 3: Subdivision curve." << std::endl;
        break;
    case '+':
        resolution++;
        break;
    case '-':
        resolution--;
        break;
    case 'a':
        subdivLevel++;
        break;
    case 'z':
        subdivLevel--;
        break;
    case 'r':
        control->clear();
        curve->clear();
        break;
    case 'h':
        printHelp();
        break;
    case 27:
        exit(0);
        break;
    }
    if (resolution < 1)
    {
        resolution = 1;
    }
    if (subdivLevel < 1)
    {
        subdivLevel = 1;
    }
    std::cout << "resolution: " << resolution << ".  Subdiv level: " << subdivLevel << "." << std::endl;
    computeCurve();
    if (curve->P.size() > 1024)
    {
        std::cout << "(Too many points to display)" << std::endl;
    }
    glutPostRedisplay();
}

void Scene::reshape(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

void Scene::drag(int x, int y)
{
    float dx = float(x - oldx) / float(width);
    float dy = -float(y - oldy) / float(height);
    control->moveActivePoint(glm::vec2(dx, dy));
    oldx = x;
    oldy = y;
    glutPostRedisplay();
}
void Scene::passiveMotion(int x, int y)
{
    control->updateActivePoint(
        glm::vec2(x / (float)width,
                  (height - y) / (float)height));
    glutPostRedisplay();
}

void Scene::mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            control->addPoint(glm::vec2(float(x) / float(width), (height - float(y)) / float(height)));
        }
        if (button == GLUT_RIGHT_BUTTON)
        {
            control->deleteActivePoint();
        }
    }
    oldx = x;
    oldy = y;
    glutPostRedisplay();
}

void Scene::computeCurve()
{
    curve->clear();
    if (control->size() > 0)
    {
        if (mode == 1)
        {
            Spline::Bezier(control, curve, resolution);
        }
        if (mode == 2)
        {
            Spline::BSpline(control, curve, resolution);
        }
        if (mode == 3)
        {
            Spline::Subdiv(control, curve, subdivLevel);
        }
    }

    // set shader data
    shader->data0 = control->P;
    shader->data1 = curve->P;
}

Scene::~Scene() {}
