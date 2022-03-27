// María López
// 2022

#include "Scene.hpp"

using namespace sf;
using namespace std;

int main ()
{
    auto scene = make_unique<Scene>();          // Usando unique_ptr<Scene> se evita un memory leak
    scene->Start();
    scene->Update();

    return 0;
}



/*! \mainpage Documentación del circuito
 * \section intro_sec Introducción
 *
 * Este proyecto ha sido creado completamente en C++ con ayuda de código de terceros, 
 como las famosas librerías SFML y Box2D; además de contener código de nuestro profesor Ángel Ballesteros.
 *
 * \section install_sec Abriendo el proyecto
 *
 * Como siempre, tenemos varias carpetas en el proyecto. Una code para el código fuente escrito por mí, otra carpeta
 * con las librerías externas usadas, otra con esta documentación y la última, la de projects, donde se encuentra el .vcxproj
 * que abrirá el proyecto en Visual Studio. Esta vez se han borrado los archivos temporales y las builds, que se generarán automáticamente
 * al darle al "Play" en el proyecto.
 *
 */

