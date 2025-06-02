#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "shaderClass.h" // Klasa do zarz¹dzania shaderami
#include "Texture.h"     // Klasa do zarz¹dzania teksturami
#include "VAO.h"         // Klasa do zarz¹dzania Vertex Array Objects

// Window dimensions
const unsigned int width = 1920;
const unsigned int height = 1080;

// Vertices for a cube (will be used for all objects)
// Ka¿dy wierzcho³ek zawiera pozycjê (x, y, z), wektor normalny (nx, ny, nz) i wspó³rzêdne tekstury (u, v).
GLfloat vertices[] = {
    // Pozycje            // Normals           // Wspó³rzêdne tekstury
    // Tylna œciana
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    // Przednia œciana
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

    // Lewa œciana
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    // Prawa œciana
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     // Dolna œciana
     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

     // Górna œciana
     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

// Wierzcho³ki dla SkyBoxa z odpowiednimi wspó³rzêdnymi tekstury,
// dostosowanymi do atlasu tekstur, aby symulowaæ sferê.
GLfloat skyBoxVertices[] = {
    // Tylna œciana (kolumna 3, wiersz 1) – odwrócone U
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  4.0f * 0.25f, 1.0f * 0.333333f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  3.0f * 0.25f, 1.0f * 0.333333f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  3.0f * 0.25f, 2.0f * 0.333333f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  3.0f * 0.25f, 2.0f * 0.333333f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  4.0f * 0.25f, 2.0f * 0.333333f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  4.0f * 0.25f, 1.0f * 0.333333f,

    // Przednia œciana (kolumna 1, wiersz 1)
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f * 0.25f, 1.0f * 0.333333f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  2.0f * 0.25f, 1.0f * 0.333333f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  2.0f * 0.25f, 2.0f * 0.333333f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  2.0f * 0.25f, 2.0f * 0.333333f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f * 0.25f, 2.0f * 0.333333f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f * 0.25f, 1.0f * 0.333333f,

    // Lewa œciana (kolumna 0, wiersz 1)
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f * 0.25f, 2.0f * 0.333333f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f * 0.25f, 2.0f * 0.333333f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f * 0.25f, 1.0f * 0.333333f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f * 0.25f, 1.0f * 0.333333f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f * 0.25f, 1.0f * 0.333333f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f * 0.25f, 2.0f * 0.333333f,

    // Prawa œciana (kolumna 2, wiersz 1) – odwrócone U
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  2.0f * 0.25f, 2.0f * 0.333333f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  3.0f * 0.25f, 2.0f * 0.333333f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  3.0f * 0.25f, 1.0f * 0.333333f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  3.0f * 0.25f, 1.0f * 0.333333f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  2.0f * 0.25f, 1.0f * 0.333333f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  2.0f * 0.25f, 2.0f * 0.333333f,

     // Dolna œciana (kolumna 1, wiersz 2) – poprawione V
     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f * 0.25f, 0.0f * 0.333333f,
      0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  2.0f * 0.25f, 0.0f * 0.333333f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  2.0f * 0.25f, 1.0f * 0.333333f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  2.0f * 0.25f, 1.0f * 0.333333f,
     -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f * 0.25f, 1.0f * 0.333333f,
     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f * 0.25f, 0.0f * 0.333333f,

     // Górna œciana (kolumna 1, wiersz 0)
     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f * 0.25f, 3.0f * 0.333333f,
     -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f * 0.25f, 2.0f * 0.333333f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  2.0f * 0.25f, 2.0f * 0.333333f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  2.0f * 0.25f, 2.0f * 0.333333f,
      0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  2.0f * 0.25f, 3.0f * 0.333333f,
     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f * 0.25f, 3.0f * 0.333333f
};

// Wierzcho³ki dla g³owy œwini, z odpowiednimi wspó³rzêdnymi tekstur.
// Zwróæ uwagê na niestandardowe przypisanie normalnych,
// które s¹ u¿ywane do okreœlenia, która tekstura powinna byæ u¿yta (g³owa czy bok).
GLfloat pigHeadVertices[] = {
    // Lewa œciana (teraz jako "przednia" œciana) - indeksy 0-5
    // Normalne (1,0,0) sugeruj¹, ¿e ta œciana bêdzie mapowana na teksturê g³owy.
    -0.5f, -0.5f, -0.5f,  1, 0, 0,  0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  1, 0, 0,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1, 0, 0,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  1, 0, 0,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  1, 0, 0,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  1, 0, 0,  0.0f, 0.0f,

    // Prawa œciana (teraz jako "tylna" œciana) - indeksy 6-11
    // Normalne (1,0,0) sugeruj¹, ¿e ta œciana bêdzie mapowana na teksturê g³owy.
     0.5f, -0.5f, -0.5f,  1, 0, 0,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1, 0, 0,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1, 0, 0,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1, 0, 0,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1, 0, 0,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1, 0, 0,  0.0f, 0.0f,

     // Przednia œciana (teraz jako "lewa" œciana) - indeksy 12-17
     // Normalne (0,0,1) sugeruj¹, ¿e ta œciana bêdzie mapowana na teksturê boku.
     -0.5f, -0.5f,  0.5f,  0, 0, 1,  0.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  0, 0, 1,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  0, 0, 1,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  0, 0, 1,  1.0f, 1.0f,
     -0.5f,  0.5f,  0.5f,  0, 0, 1,  0.0f, 1.0f,
     -0.5f, -0.5f,  0.5f,  0, 0, 1,  0.0f, 0.0f,

     // Tylna œciana (teraz jako "prawa" œciana) - indeksy 18-23
     // Normalne (0,0,1) sugeruj¹, ¿e ta œciana bêdzie mapowana na teksturê boku.
     -0.5f, -0.5f, -0.5f,  0, 0, 1,  0.0f, 0.0f,
      0.5f, -0.5f, -0.5f,  0, 0, 1,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  0, 0, 1,  1.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  0, 0, 1,  1.0f, 1.0f,
     -0.5f,  0.5f, -0.5f,  0, 0, 1,  0.0f, 1.0f,
     -0.5f, -0.5f, -0.5f,  0, 0, 1,  0.0f, 0.0f,

     // Dolna œciana - indeksy 24-29
     // Normalne (0,1,0) sugeruj¹, ¿e ta œciana bêdzie mapowana na teksturê boku/góry.
     -0.5f, -0.5f, -0.5f,  0, 1, 0,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0, 1, 0,  1.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  0, 1, 0,  1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  0, 1, 0,  1.0f, 0.0f,
     -0.5f, -0.5f,  0.5f,  0, 1, 0,  0.0f, 0.0f,
     -0.5f, -0.5f, -0.5f,  0, 1, 0,  0.0f, 1.0f,

     // Górna œciana - indeksy 30-35
     // Normalne (0,1,0) sugeruj¹, ¿e ta œciana bêdzie mapowana na teksturê boku/góry.
     -0.5f,  0.5f, -0.5f,  0, 1, 0,  0.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  0, 1, 0,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  0, 1, 0,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  0, 1, 0,  1.0f, 0.0f,
     -0.5f,  0.5f,  0.5f,  0, 1, 0,  0.0f, 0.0f,
     -0.5f,  0.5f, -0.5f,  0, 1, 0,  0.0f, 1.0f
};

// Zmienne kamery
glm::vec3 cameraPos = glm::vec3(0.0f, 2.0f, 5.0f);   // Pozycja kamery
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); // Kierunek, w którym patrzy kamera
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);     // Wektor "w górê" dla kamery

// Timing
float deltaTime = 0.0f; // Czas miêdzy bie¿¹c¹ a poprzedni¹ klatk¹
float lastFrame = 0.0f; // Czas ostatniej klatki

// Zmienne myszy
bool firstMouse = true;   // Flaga do obs³ugi pierwszego ruchu mysz¹
float lastX = width / 2.0f; // Poprzednia pozycja X myszy
float lastY = height / 2.0f; // Poprzednia pozycja Y myszy
float yaw = -90.0f;       // Obrót kamery wokó³ osi Y (pocz¹tkowo skierowana w stronê -Z)
float pitch = 0.0f;       // Obrót kamery wokó³ osi X

// Pozycja i ruch creepera
glm::vec3 creeperPos = glm::vec3(3.0f, 0.0f, 3.0f);    // Pocz¹tkowa pozycja creepera (prawo-przód od domu)
glm::vec3 creeperFront = glm::vec3(0.0f, 0.0f, -1.0f); // Pocz¹tkowy kierunek, w którym creeper jest zwrócony

// Pozycja œwiat³a (s³oñca)
glm::vec3 lightPos = glm::vec3(5.0f, 5.0f, 5.0f); // Pocz¹tkowa pozycja Ÿród³a œwiat³a
float lightAngle = 0.0f;                         // K¹t obrotu œwiat³a (symulacja ruchu s³oñca)
GLfloat lightSpeed = 1.0f;                       // Prêdkoœæ obrotu œwiat³a

// Zmienne dla g³owy œwini
glm::vec3 pigHeadPos = glm::vec3(7.0f, 2.5f, 7.0f); // Pozycja g³owy œwini
glm::vec3 pigHeadScale = glm::vec3(2.5f);        // Pocz¹tkowa skala g³owy œwini


// Prototypy funkcji
/**
 * @brief Callback do zmiany rozmiaru framebuffer'a.
 * @param window WskaŸnik na okno GLFW.
 * @param width Nowa szerokoœæ okna.
 * @param height Nowa wysokoœæ okna.
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/**
 * @brief Przetwarza dane wejœciowe z klawiatury.
 * @param window WskaŸnik na okno GLFW.
 */
void processInput(GLFWwindow* window);

/**
 * @brief Callback do obs³ugi ruchu myszy.
 * @param window WskaŸnik na okno GLFW.
 * @param xpos Bie¿¹ca pozycja X kursora.
 * @param ypos Bie¿¹ca pozycja Y kursora.
 */
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

/**
 * @brief Renderuje pojedynczy szeœcian.
 * @param shader Obiekt shadera do u¿ycia.
 * @param texture Obiekt tekstury do na³o¿enia na szeœcian.
 * @param position Pozycja szeœcianu w œwiecie.
 * @param scale Skala szeœcianu.
 */
void renderCube(Shader& shader, Texture& texture, glm::vec3 position, glm::vec3 scale = glm::vec3(1.0f));

/**
 * @brief Renderuje SkyBox.
 * @param shader Obiekt shadera do u¿ycia.
 * @param skyBoxTex Obiekt tekstury dla SkyBoxa.
 */
void renderSkyBox(Shader& shader, Texture& skyBoxTex);

/**
 * @brief Renderuje drzewo sk³adaj¹ce siê z bloków.
 * @param shader Obiekt shadera do u¿ycia.
 * @param woodTex Obiekt tekstury drewna.
 * @param leavesTex Obiekt tekstury liœci.
 */
void renderTree(Shader& shader, Texture& woodTex, Texture& leavesTex);

/**
 * @brief Renderuje prosty dom sk³adaj¹cy siê z bloków.
 * @param shader Obiekt shadera do u¿ycia.
 * @param houseTex Obiekt tekstury domu.
 */
void renderHouse(Shader& shader, Texture& houseTex);

/**
 * @brief Renderuje creepera sk³adaj¹cego siê z bloków.
 * @param shader Obiekt shadera do u¿ycia.
 * @param creeperTex Obiekt tekstury creepera.
 */
void renderCreeper(Shader& shader, Texture& creeperTex);

/**
 * @brief Renderuje g³owê œwini, wykorzystuj¹c dwie ró¿ne tekstury dla ró¿nych œcian.
 * @param shader Obiekt shadera do u¿ycia.
 * @param headTex Obiekt tekstury dla "przedniej" i "tylnej" œciany g³owy (np. z pyskiem).
 * @param sideTex Obiekt tekstury dla bocznych, górnej i dolnej œciany g³owy.
 * @param position Pozycja g³owy œwini w œwiecie.
 * @param scale Skala g³owy œwini.
 */
void renderPigHead(Shader& shader, Texture& headTex, Texture& sideTex, glm::vec3 position, glm::vec3 scale);

/**
 * @brief Aktualizuje pozycjê i kierunek creepera na podstawie danych wejœciowych.
 * @param deltaTime Czas, jaki up³yn¹³ od ostatniej klatki.
 * @param window WskaŸnik na okno GLFW (do sprawdzania stanu klawiszy).
 */
void updateCreeper(float deltaTime, GLFWwindow* window);

bool blurEnabled = true; // Flaga okreœlaj¹ca, czy efekt rozmycia jest w³¹czony (domyœlnie w³¹czony)

int main()
{
    // Inicjalizacja GLFW
    glfwInit();
    // Ustawienie wersji OpenGL na 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Tworzenie okna
    GLFWwindow* window = glfwCreateWindow(width, height, "Maincamp - Projekt", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Ustawienie kontekstu OpenGL dla bie¿¹cego okna
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Rejestracja callbacka dla zmiany rozmiaru okna
    glfwSetCursorPosCallback(window, mouse_callback);               // Rejestracja callbacka dla ruchu myszy
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);    // Ukrycie i zablokowanie kursora myszy

    // £adowanie GLAD (zarz¹dzanie wskaŸnikami funkcji OpenGL)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Konfiguracja globalnego stanu OpenGL
    glEnable(GL_DEPTH_TEST); // W³¹czenie testu g³êbi dla prawid³owego renderowania 3D

    // Generowanie i bindowanie framebuffer'a (FBO) do renderowania poza ekranem
    unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // Generowanie i do³¹czanie tekstury kolorów do FBO
    unsigned int textureColorbuffer;
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    // Przydzielenie pamiêci dla tekstury bez inicjalizacji danych
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    // Ustawienie filtrów tekstury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Do³¹czenie tekstury do FBO jako za³¹cznik kolorów
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

    // Generowanie i do³¹czanie renderbuffer'a (dla g³êbi i stencilu) do FBO
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    // Przydzielenie pamiêci dla renderbuffer'a
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    // Do³¹czenie renderbuffer'a do FBO jako za³¹cznik g³êbi i stencilu
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    // Sprawdzenie kompletnoœci framebuffer'a
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // Odwi¹zanie FBO, aby renderowaæ z powrotem na domyœlny framebuffer

    // Budowanie i kompilacja shaderów
    Shader defaultShader("default.vert", "default.frag");     // Shader dla wiêkszoœci obiektów w scenie
    Shader lightCubeShader("lightCube.vert", "lightCube.frag"); // Shader dla obiektu reprezentuj¹cego œwiat³o
    Shader skyBoxShader("skyBox.vert", "skyBox.frag");       // Shader dla SkyBoxa
    Shader blurShader("Framebuffer.vert", "Framebuffer.frag"); // Shader do efektu rozmycia (post-processing)
    Shader defaultScreenShader("defaultScreen.vert", "defaultScreen.frag"); // Shader do renderowania tekstury na pe³nym ekranie bez efektów

    // £adowanie tekstur
    Texture woodTex("tree.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture leavesTex("leaves.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture houseTex("house.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture creeperTex("creeper.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture groundTex("grass.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture skyTex("skyBox.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture pigHeadTex("pig_head.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture pigSideTex("pig_side.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    // Konfiguracja Vertex Array Object (VAO) dla szeœcianu
    VAO cubeVAO;
    cubeVAO.Bind();
    VBO cubeVBO(vertices, sizeof(vertices)); // Tworzenie Vertex Buffer Object (VBO) z danymi wierzcho³ków
    // £¹czenie atrybutów wierzcho³ków (pozycja, normalne, wspó³rzêdne tekstury) z VAO
    cubeVAO.LinkAttrib(cubeVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    cubeVAO.LinkAttrib(cubeVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    cubeVAO.LinkAttrib(cubeVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    cubeVAO.Unbind(); // Odwi¹zanie VAO
    cubeVBO.Unbind(); // Odwi¹zanie VBO

    // Konfiguracja VAO dla SkyBoxa
    VAO skyVAO;
    skyVAO.Bind();
    VBO skyVBO(skyBoxVertices, sizeof(skyBoxVertices));
    skyVAO.LinkAttrib(skyVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    skyVAO.LinkAttrib(skyVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    skyVAO.LinkAttrib(skyVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    skyVAO.Unbind();
    skyVBO.Unbind();

    // Konfiguracja VAO dla g³owy œwini
    VAO pigHeadVAO;
    pigHeadVAO.Bind();
    VBO pigHeadVBO(pigHeadVertices, sizeof(pigHeadVertices));
    pigHeadVAO.LinkAttrib(pigHeadVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    pigHeadVAO.LinkAttrib(pigHeadVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    pigHeadVAO.LinkAttrib(pigHeadVBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    pigHeadVAO.Unbind();
    pigHeadVBO.Unbind();

    // Kolory nieba i œwiat³a w zale¿noœci od pory dnia
    glm::vec4 defaultSkyColor = glm::vec4(0.53f, 0.81f, 0.92f, 1.0f); // Kolor nieba w dzieñ
    glm::vec4 nightColor = glm::vec4(0.13f, 0.31f, 0.42f, 1.0f);     // Kolor nieba w nocy

    // Wierzcho³ki dla pe³noekranowego kwadratu (do post-processingu)
    float quadVertices[] = {
        // pozycje   // wspó³rzêdne tekstury
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // G³ówna pêtla renderowania
    while (!glfwWindowShouldClose(window))
    {
        // Logika czasu na klatkê
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Przetwarzanie danych wejœciowych
        processInput(window);

        // --- Aktualizacja pozycji œwiat³a (ruch s³oñca) ---
        lightAngle += lightSpeed * deltaTime; // Zwiêkszanie k¹ta obrotu œwiat³a
        if (lightAngle > 360.0f) lightAngle -= 360.0f; // Resetowanie k¹ta po pe³nym obrocie
        // Obliczanie pozycji œwiat³a na okrêgu
        lightPos.x = 30.0f * cos(lightAngle);
        lightPos.y = 30.0f * sin(lightAngle);

        // Aktualizacja pozycji creepera
        updateCreeper(deltaTime, window);

        // --- 1. RENDEROWANIE SCENY DO FRAMEBUFFERA ---
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer); // Bindowanie FBO do renderowania do tekstury
        glEnable(GL_DEPTH_TEST); // W³¹czenie testu g³êbi

        // Interpolacja koloru nieba w zale¿noœci od k¹ta œwiat³a (symulacja dnia/nocy)
        glm::vec4 skyColor = glm::mix(nightColor, defaultSkyColor, sin(lightAngle));
        glClearColor(skyColor.x, skyColor.y, skyColor.z, skyColor.w); // Ustawienie koloru t³a
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);           // Czyszczenie buforów koloru i g³êbi

        defaultShader.Activate(); // Aktywacja g³ównego shadera

        // Interpolacja koloru œwiat³a w zale¿noœci od k¹ta œwiat³a (symulacja dnia/nocy)
        glm::vec4 defaultLightColor = glm::vec4(1.0f, 1.0f, 0.9f, 1.0f); // Kolor œwiat³a w dzieñ
        glm::vec3 lightColor = glm::mix(nightColor, defaultLightColor, sin(lightAngle));
        // Ustawienie uniformów shadera dla oœwietlenia
        glUniform3f(glGetUniformLocation(defaultShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z);
        glUniform3f(glGetUniformLocation(defaultShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(glGetUniformLocation(defaultShader.ID, "viewPos"), cameraPos.x, cameraPos.y, cameraPos.z);
        glUniform1f(glGetUniformLocation(defaultShader.ID, "material.shininess"), 32.0f);

        // Tworzenie macierzy projekcji i widoku
        glm::mat4 projection = glm::perspective(glm::radians(100.0f), (float)width / (float)height, 0.1f, 200.0f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        // Przekazanie macierzy do shadera
        glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "view"), 1, GL_FALSE, &view[0][0]);

        // Renderowanie pod³o¿a
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
        model = glm::scale(model, glm::vec3(50.0f, 1.0f, 50.0f));
        glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "model"), 1, GL_FALSE, &model[0][0]);
        groundTex.Bind(); // Aktywacja tekstury pod³o¿a
        cubeVAO.Bind();   // Bindowanie VAO dla szeœcianu
        glDrawArrays(GL_TRIANGLES, 0, 36); // Rysowanie szeœcianu

        // Renderowanie obiektów sceny
        renderTree(defaultShader, woodTex, leavesTex);      // Renderowanie drzewa
        renderHouse(defaultShader, houseTex);               // Renderowanie domu
        renderCreeper(defaultShader, creeperTex);           // Renderowanie creepera
        renderPigHead(defaultShader, pigHeadTex, pigSideTex, pigHeadPos, pigHeadScale); // Renderowanie g³owy œwini

        // Skybox
        skyVAO.Bind();           // Bindowanie VAO dla SkyBoxa
        skyBoxShader.Activate(); // Aktywacja shadera SkyBoxa

        // Przekazanie koloru œwiat³a do shadera SkyBoxa
        GLuint skyBoxLightColorLoc = glGetUniformLocation(skyBoxShader.ID, "lightColor");
        glm::vec3 skyBoxlightColor = glm::mix(nightColor, defaultLightColor, sin(lightAngle));
        glUniform3f(skyBoxLightColorLoc, skyBoxlightColor.x, skyBoxlightColor.y, skyBoxlightColor.z);

        // Przekazanie macierzy projekcji i widoku do shadera SkyBoxa
        GLuint skyProjectionLoc = glGetUniformLocation(skyBoxShader.ID, "projection");
        glUniformMatrix4fv(skyProjectionLoc, 1, GL_FALSE, &projection[0][0]);
        GLuint skyViewLoc = glGetUniformLocation(skyBoxShader.ID, "view");
        glUniformMatrix4fv(skyViewLoc, 1, GL_FALSE, &view[0][0]);

        renderSkyBox(skyBoxShader, skyTex); // Renderowanie SkyBoxa

        // Œwiat³o jako szeœcian
        lightCubeShader.Activate(); // Aktywacja shadera dla szeœcianu œwiat³a
        // Przekazanie macierzy projekcji i widoku
        glUniformMatrix4fv(glGetUniformLocation(lightCubeShader.ID, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(lightCubeShader.ID, "view"), 1, GL_FALSE, &view[0][0]);
        // Utworzenie macierzy modelu dla szeœcianu œwiat³a
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(5.0f)); // Skalowanie szeœcianu œwiat³a
        glUniformMatrix4fv(glGetUniformLocation(lightCubeShader.ID, "model"), 1, GL_FALSE, &model[0][0]);
        cubeVAO.Bind(); // Bindowanie VAO dla szeœcianu (do renderowania szeœcianu œwiat³a)
        glDrawArrays(GL_TRIANGLES, 0, 36); // Rysowanie szeœcianu œwiat³a

        // 2. Renderowanie pe³noekranowego kwadratu z efektem rozmycia (jeœli w³¹czony) lub normalnie
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // Powrót do domyœlnego framebuffer'a (ekranu)
        glDisable(GL_DEPTH_TEST);             // Wy³¹czenie testu g³êbi (niepotrzebne dla 2D kwadratu)
        glClear(GL_COLOR_BUFFER_BIT);         // Czyszczenie bufora koloru

        // Wybór shadera do post-processingu
        if (blurEnabled) {
            blurShader.Activate(); // Aktywacja shadera do rozmycia
        }
        else {
            defaultScreenShader.Activate(); // Aktywacja shadera do renderowania bez zmian
        }

        glBindVertexArray(quadVAO);               // Bindowanie VAO pe³noekranowego kwadratu
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer); // Bindowanie tekstury z wyrenderowan¹ scen¹
        glDrawArrays(GL_TRIANGLES, 0, 6);         // Rysowanie kwadratu

        // Zamiana buforów i przetwarzanie zdarzeñ
        glfwSwapBuffers(window); // Wymiana buforów (wyœwietlenie wyrenderowanej klatki)
        glfwPollEvents();        // Przetwarzanie zdarzeñ (np. wejœcie z klawiatury/myszy)
    }

    // Czyszczenie zasobów OpenGL
    cubeVAO.Delete();
    cubeVBO.Delete();
    woodTex.Delete();
    leavesTex.Delete();
    houseTex.Delete();
    creeperTex.Delete();
    groundTex.Delete();
    defaultShader.Delete();
    lightCubeShader.Delete();
    pigSideTex.Delete(); // Usuniêcie tekstury boku œwini

    glfwTerminate(); // Zakoñczenie pracy GLFW
    return 0;        // Pomyœlne zakoñczenie programu
}

/**
 * @brief Aktualizuje pozycjê i kierunek creepera na podstawie danych wejœciowych z klawiatury.
 * Creeper porusza siê w p³aszczyŸnie XZ i ma ograniczone pole ruchu.
 * @param deltaTime Czas, jaki up³yn¹³ od ostatniej klatki, u¿ywany do skalowania ruchu.
 * @param window WskaŸnik na okno GLFW, u¿ywany do sprawdzania stanu klawiszy strza³ek.
 */
void updateCreeper(float deltaTime, GLFWwindow* window) {
    const float moveSpeed = 3.0f * deltaTime; // Bazowa prêdkoœæ ruchu creepera
    bool moved = false; // Flaga, czy creeper siê poruszy³ w tej klatce

    // Obs³uga ruchu klawiszami strza³ek
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        creeperPos.z -= moveSpeed; // Ruch do przodu (wzglêdem pocz¹tkowego kierunku -Z)
        creeperFront = glm::vec3(0.0f, 0.0f, -1.0f); // Ustawienie kierunku przodem
        moved = true;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        creeperPos.z += moveSpeed; // Ruch do ty³u
        creeperFront = glm::vec3(0.0f, 0.0f, 1.0f);  // Ustawienie kierunku ty³em
        moved = true;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        creeperPos.x -= moveSpeed; // Ruch w lewo
        creeperFront = glm::vec3(-1.0f, 0.0f, 0.0f); // Ustawienie kierunku w lewo
        moved = true;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        creeperPos.x += moveSpeed; // Ruch w prawo
        creeperFront = glm::vec3(1.0f, 0.0f, 0.0f);  // Ustawienie kierunku w prawo
        moved = true;
    }

    // Ograniczenie pozycji creepera do okreœlonego zakresu na p³aszczyŸnie XZ
    creeperPos.x = glm::clamp(creeperPos.x, -5.0f, 5.0f);
    creeperPos.z = glm::clamp(creeperPos.z, -5.0f, 5.0f);

    // Kierunek creepera jest aktualizowany tylko wtedy, gdy siê poruszy³,
    // w przeciwnym razie zachowuje poprzedni kierunek.
    if (!moved) {
        // Zachowaj bie¿¹cy kierunek
    }
}

/**
 * @brief Renderuje pojedynczy szeœcian w scenie, stosuj¹c transformacje modelu.
 * @param shader Obiekt shadera, który ma zostaæ u¿yty do renderowania szeœcianu.
 * @param texture Obiekt tekstury, która ma zostaæ na³o¿ona na szeœcian.
 * @param position Wektor glm::vec3 okreœlaj¹cy pozycjê szeœcianu w przestrzeni œwiata.
 * @param scale Wektor glm::vec3 okreœlaj¹cy skalê szeœcianu (domyœlnie glm::vec3(1.0f) - brak skalowania).
 */
void renderCube(Shader& shader, Texture& texture, glm::vec3 position, glm::vec3 scale)
{
    // Utworzenie macierzy modelu, inicjalizacja jako macierz jednostkowa.
    glm::mat4 model = glm::mat4(1.0f);
    // Przesuniêcie szeœcianu do okreœlonej pozycji.
    model = glm::translate(model, position);
    // Skalowanie szeœcianu.
    model = glm::scale(model, scale);

    // Pobranie lokalizacji uniformu "model" w shaderze.
    GLuint modelLoc = glGetUniformLocation(shader.ID, "model");
    // Ustawienie macierzy modelu w shaderze.
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

    // Aktywacja i bindowanie tekstury.
    texture.Bind();
    // Rysowanie 36 wierzcho³ków szeœcianu (dwanaœcie trójk¹tów, ka¿dy po 3 wierzcho³ki).
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

/**
 * @brief Renderuje SkyBox, który otacza ca³¹ scenê.
 * SkyBox jest skalowany na du¿¹ wartoœæ, aby zawsze znajdowa³ siê poza zasiêgiem widzenia.
 * @param shader Obiekt shadera SkyBoxa.
 * @param skyBoxTex Obiekt tekstury dla SkyBoxa.
 */
void renderSkyBox(Shader& shader, Texture& skyBoxTex)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(100.0f)); // Skalowanie SkyBoxa, aby by³ bardzo du¿y

    // Przekazanie macierzy modelu do shadera SkyBoxa
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, &model[0][0]);
    skyBoxTex.Bind(); // Aktywacja tekstury SkyBoxa
    glDrawArrays(GL_TRIANGLES, 0, 36); // Rysowanie SkyBoxa (szeœcianu)
}

/**
 * @brief Renderuje drzewo, sk³adaj¹ce siê z kilku bloków drewna i liœci.
 * Wykorzystuje funkcjê `renderCube` do rysowania poszczególnych bloków.
 * @param shader Obiekt shadera do u¿ycia.
 * @param woodTex Tekstura drewna.
 * @param leavesTex Tekstura liœci.
 */
void renderTree(Shader& shader, Texture& woodTex, Texture& leavesTex)
{
    // Pieñ (4 bloki wysokoœci)
    for (int i = 0; i < 4; i++) {
        renderCube(shader, woodTex, glm::vec3(2.0f, 0.5f + i, 0.0f));
    }

    // Liœcie na górze
    renderCube(shader, leavesTex, glm::vec3(2.0f, 3.5f, 0.0f));
    renderCube(shader, leavesTex, glm::vec3(2.0f, 4.5f, 0.0f));
    renderCube(shader, leavesTex, glm::vec3(1.0f, 3.5f, 0.0f));
    renderCube(shader, leavesTex, glm::vec3(3.0f, 3.5f, 0.0f));
    renderCube(shader, leavesTex, glm::vec3(2.0f, 3.5f, 1.0f));
    renderCube(shader, leavesTex, glm::vec3(2.0f, 3.5f, -1.0f));
}

/**
 * @brief Renderuje prosty dom sk³adaj¹cy siê z bloków, z wyciêtymi drzwiami i oknami.
 * Wykorzystuje funkcjê `renderCube` do rysowania poszczególnych bloków.
 * @param shader Obiekt shadera do u¿ycia.
 * @param houseTex Tekstura domu.
 */
void renderHouse(Shader& shader, Texture& houseTex)
{
    // Podstawa domu (4x4x4 bloki)
    for (int x = 0; x < 4; x++) {
        for (int z = 0; z < 4; z++) {
            for (int y = 0; y < 4; y++) {
                // Renderowanie tylko zewnêtrznych œcian i dachu/pod³ogi, aby utworzyæ pusty w œrodku dom
                if (y == 0 || y == 3 || x == 0 || x == 3 || z == 0 || z == 3) {
                    // Pomijanie bloków dla drzwi i okien
                    if (!(y == 0 && x == 1 && z == 0)) { // Drzwi (na poziomie Y=0, X=1, Z=0)
                        // Okna (na poziomach Y=1 i Y=2, w okreœlonych miejscach XZ)
                        if (!((y == 1 || y == 2) && ((x == 1 && (z == 1 || z == 2)) || (z == 1 && (x == 1 || x == 2))))) {
                            renderCube(shader, houseTex, glm::vec3(-5.0f + x, 0.5f + y, -3.0f + z));
                        }
                    }
                }
            }
        }
    }
}

/**
 * @brief Renderuje postaæ creepera, sk³adaj¹c¹ siê z dwóch bloków i obracaj¹c¹ siê w kierunku ruchu.
 * @param shader Obiekt shadera do u¿ycia.
 * @param creeperTex Tekstura creepera.
 */
void renderCreeper(Shader& shader, Texture& creeperTex)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, creeperPos); // Przesuniêcie creepera do jego aktualnej pozycji
    // Obrót creepera tak, aby by³ zwrócony w kierunku ruchu (na podstawie creeperFront)
    model = glm::rotate(model, atan2(creeperFront.x, creeperFront.z), glm::vec3(0.0f, 1.0f, 0.0f));

    // Dolny blok creepera
    glm::mat4 bottomModel = model;
    bottomModel = glm::translate(bottomModel, glm::vec3(0.0f, 0.5f, 0.0f)); // Przesuniêcie dolnego bloku
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, &bottomModel[0][0]);
    creeperTex.Bind(); // Aktywacja tekstury creepera
    glDrawArrays(GL_TRIANGLES, 0, 36); // Rysowanie dolnego bloku

    // Górny blok creepera
    glm::mat4 topModel = model;
    topModel = glm::translate(topModel, glm::vec3(0.0f, 1.5f, 0.0f)); // Przesuniêcie górnego bloku
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, &topModel[0][0]);
    creeperTex.Bind(); // Aktywacja tekstury creepera
    glDrawArrays(GL_TRIANGLES, 0, 36); // Rysowanie górnego bloku
}

/**
 * @brief Renderuje g³owê œwini z wykorzystaniem dwóch ró¿nych tekstur dla poszczególnych œcian.
 * Wierzcho³ki `pigHeadVertices` s¹ specjalnie zdefiniowane, aby umo¿liwiæ mapowanie tekstur na podstawie normalnych.
 * @param shader Obiekt shadera do u¿ycia.
 * @param headTex Tekstura przeznaczona dla "przedniej" i "tylnej" œciany g³owy (z pyszczkiem/twarz¹).
 * @param sideTex Tekstura przeznaczona dla bocznych, górnej i dolnej œciany g³owy.
 * @param position Pozycja g³owy œwini w œwiecie.
 * @param scale Skala g³owy œwini.
 */
void renderPigHead(Shader& shader, Texture& headTex, Texture& sideTex, glm::vec3 position, glm::vec3 scale)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position); // Przesuniêcie g³owy œwini do jej pozycji
    // Obrót o 90 stopni wokó³ osi Y, aby tekstura pyszczka by³a na odpowiedniej œcianie
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale); // Skalowanie g³owy œwini

    GLuint modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

    // Renderowanie œcian z oryginalnymi indeksami, ale z odpowiedni¹ tekstur¹
    // Œciany o normalnych (1,0,0) (czyli oryginalnie lewa i prawa, teraz przekrêcone na przód i ty³)
    headTex.Bind(); // Bindowanie tekstury g³owy (z pyszczkiem)
    glDrawArrays(GL_TRIANGLES, 0, 6); // Renderowanie "przedniej" œciany (oryginalnie lewej)
    glDrawArrays(GL_TRIANGLES, 6, 6); // Renderowanie "tylnej" œciany (oryginalnie prawej)

    // Œciany o normalnych (0,0,1) i (0,1,0) (czyli oryginalnie przednia, tylna, dolna i górna)
    sideTex.Bind(); // Bindowanie tekstury bocznej/górnej/dolnej
    glDrawArrays(GL_TRIANGLES, 12, 6); // Renderowanie "lewej" œciany (oryginalnie przedniej)
    glDrawArrays(GL_TRIANGLES, 18, 6); // Renderowanie "prawej" œciany (oryginalnie tylnej)
    glDrawArrays(GL_TRIANGLES, 24, 6); // Renderowanie dolnej œciany
    glDrawArrays(GL_TRIANGLES, 30, 6); // Renderowanie górnej œciany
}

/**
 * @brief Przetwarza dane wejœciowe z klawiatury w celu sterowania kamer¹, œwiat³em i efektem rozmycia.
 * @param window WskaŸnik na okno GLFW.
 */
void processInput(GLFWwindow* window)
{
    // Zamkniêcie okna po naciœniêciu klawisza ESC
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Prêdkoœæ poruszania siê kamery, skalowana przez deltaTime
    float cameraSpeed = 5.0f * deltaTime;
    // Ruch kamery do przodu/ty³u (W/S)
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    // Ruch kamery w lewo/prawo (A/D)
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    // Ruch kamery w górê/dó³ (SPACE/LEFT_SHIFT)
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraUp;
    // Zwiêkszenie/zmniejszenie prêdkoœci œwiat³a (+/-)
    if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
        lightSpeed += 0.001f;
    if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
        if (lightSpeed > 0.05f) lightSpeed -= 0.001f;
    // Zwiêkszenie/zmniejszenie skali g³owy œwini (KP_ADD/KP_SUBTRACT)
    if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) {
        pigHeadScale += glm::vec3(0.1f) * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) {
        pigHeadScale -= glm::vec3(0.1f) * deltaTime;
        // Zabezpieczenie przed ujemn¹ skal¹
        if (pigHeadScale.x < 0.1f) pigHeadScale = glm::vec3(0.1f);
    }

    // Statyczna flaga do obs³ugi pojedynczego wciœniêcia klawisza 'B'
    static bool blurKeyPressed = false;
    // Prze³¹czanie efektu rozmycia po naciœniêciu klawisza 'B'
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        if (!blurKeyPressed) { // Sprawdzenie, czy klawisz nie by³ ju¿ wciœniêty w poprzedniej klatce
            blurEnabled = !blurEnabled; // Zmiana stanu w³¹czenia/wy³¹czenia rozmycia
            blurKeyPressed = true;      // Ustawienie flagi na true
        }
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE) {
        blurKeyPressed = false; // Resetowanie flagi po zwolnieniu klawisza
    }
}

/**
 * @brief Callback wywo³ywany, gdy rozmiar okna zostanie zmieniony.
 * Aktualizuje rozmiar viewportu OpenGL, aby dopasowaæ go do nowego rozmiaru okna.
 * @param window WskaŸnik na okno GLFW.
 * @param width Nowa szerokoœæ okna.
 * @param height Nowa wysokoœæ okna.
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height); // Ustawienie nowego rozmiaru viewportu
}

/**
 * @brief Callback wywo³ywany, gdy kursor myszy zostanie przesuniêty.
 * Oblicza przesuniêcie myszy i aktualizuje k¹ty yaw i pitch kamery, a nastêpnie przelicza wektor cameraFront.
 * @param window WskaŸnik na okno GLFW.
 * @param xpos Bie¿¹ca pozycja X kursora.
 * @param ypos Bie¿¹ca pozycja Y kursora.
 */
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    // Inicjalizacja pozycji myszy przy pierwszym wejœciu
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    // Obliczenie przesuniêcia myszy od ostatniej klatki
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Odwrócone, poniewa¿ wspó³rzêdne Y OpenGL rosn¹ w górê, a Y ekranu w dó³
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // Czu³oœæ myszy
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    // Aktualizacja k¹tów yaw i pitch
    yaw += xoffset;
    pitch += yoffset;

    // Ograniczenie k¹ta pitch, aby zapobiec "przewróceniu" kamery
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // Obliczenie nowego wektora cameraFront na podstawie k¹tów yaw i pitch
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front); // Normalizacja wektora
}