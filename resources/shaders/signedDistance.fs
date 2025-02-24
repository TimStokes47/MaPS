#version 330 core
in vec2 position;
out vec4 FragColor;

vec2 centres[] = {vec2(40.0f, 50.0f), vec2(20.0f, 30.0f)};

float circle(vec2 samplePosition, vec2 centre, float radius){
    return length(samplePosition - centre) - radius;
}

void main()
{
   float d = 150.0f;
   for (int i = 0; i < 2; i++){
      d = min(d, circle(position, centres[i], 20.0f));
   }
   if (d > 0)
      FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
   else
      FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}