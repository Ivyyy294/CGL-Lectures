#include "Physics.h"

void Physics::Run(GameObject::Vec& vec)
{
   for (int i = 0; i < vec.size(); ++i)
   {
       GameObject* obj1 = vec[i];

      for (int j = 0; j < vec.size(); ++j)
      {
          GameObject* obj2 = vec[j];

          if (obj1 == obj2)
              continue;
          else
              ResolveCollision(obj1, obj2);
      }
   }
}

void Physics::ResolveCollision(GameObject* obj1, GameObject* obj2)
{
    Circle* circle = dynamic_cast<Circle*>(obj1);
    Wall* wall2 = dynamic_cast<Wall*>(obj2);
    Circle* circle2 = dynamic_cast<Circle*>(obj2);

    if (circle != nullptr && wall2 != nullptr)
        ResolveCollision(circle, wall2);
    else if (circle != nullptr && circle2 != nullptr)
        ResolveCollision(circle, circle2);
}

void Physics::ResolveCollision(Circle* circle, Wall* wall) {
   glm::vec2 start = wall->Start();
   glm::vec2 end = wall->End();
   glm::vec2 center = circle->Position();
   float radius = circle->Radius();

   float dx = end.x - start.x;
   float dy = end.y - start.y;

   float A = dx * dx + dy * dy;
   float B = 2 * ((start.x - center.x) * dx + (start.y - center.y) * dy);
   float C = (start.x - center.x) * (start.x - center.x) +
            (start.y - center.y) * (start.y - center.y) - radius * radius;

   float D = B * B - 4 * A * C; // Diskriminante

   if (D < 0) {
      return; // Keine Schnittpunkte
   }

   // Berechne die beiden möglichen Werte für t
   float t1 = (-B + sqrt(D)) / (2 * A);
   float t2 = (-B - sqrt(D)) / (2 * A);
   float t = 0.f;

   // Prüfe, ob mindestens ein t-Wert im Bereich [0,1] liegt
   if (t1 >= 0 && t1 <= 1)
	   t = t1;
	else if (t2 >= 0 && t2 <= 1)
      t = t2;
   else
	   return;

   glm::vec2 cp = wall->GetPointAtTime(t);
   glm::vec2 direction = center - cp;
   
   if (!circle->IsStatic())
       circle->ApplyForce(direction);
}

void Physics::ResolveCollision(Circle* circle1, Circle* circle2)
{
    glm::vec2 direction = circle1->Position() - circle2->Position();
    float distance = glm::length(direction);

    if (distance <= circle1->Radius() + circle2->Radius())
    {
        float vel1 = glm::length(circle1->Velocity());
        float vel2 = glm::length(circle2->Velocity());

        //if (vel1 < vel2)
         circle1->ApplyForce(direction);
    }
}
