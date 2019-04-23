//HSVからRGBに変換します
/*引数
 *float H 0~360　色
 *float S 0.0~1.0 透明度
 *float V 0.0~1.0 明るさ
 */

typedef struct
{
  uint32_t R;
  uint32_t G;
  uint32_t B;
}Color;

void HSVtoRGB(float H, float  S,float  V,Color *rgb)
{
  uint32_t Hi;
  float f, p, q, t;

  Hi = ((uint32_t)(H / 60)) % 6;
  f = H / 60 - Hi;
  p = V * (1 - S);
  q = V * (1 - f * S);
  t = V * (1 - (1 - f) * S);

  V *= PANELRESOL;
  p *= PANELRESOL;
  q *= PANELRESOL;
   t *= PANELRESOL;

  switch (Hi)
  {
	case 0: rgb->R = V; rgb->G = t; rgb->B = p; break;
	case 1: rgb->R = q; rgb->G = V; rgb->B = p; break;
	case 2: rgb->R = p; rgb->G = V; rgb->B = t; break;
	case 3: rgb->R = p; rgb->G = q; rgb->B = V; break;
	case 4: rgb->R = t; rgb->G = p; rgb->B = V; break;
	case 5: rgb->R = V; rgb->G = p; rgb->B = q; break;
  }
}
