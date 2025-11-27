using System;

namespace IvyyyAI
{
    //slope intercept formular
    // y = mx+b
    // y = m (x-c)^k+b
    // m = slope
    // k = exponent
    // b = y-intercept vertical shift
    // c = x-intercept horizontal shift

    //logistic
    // y = (k (1/(1+(1000))))
    public class IvyyyResponseCurve
    {
        public enum CurveType
        {
            None,
            Linear,
            //Exponential,
            Logistic,
            //Logit
        }

        private CurveType m_type;
        private float m_m;
        private float m_k;
        private float m_b;
        private float m_c;

        public IvyyyResponseCurve (CurveType type, float m = 1f, float k = 1f, float b = 0f, float c = 0f)
        {
            m_type = type;
            m_m = m;
            m_k = k;
            m_b = b;
            m_c = c;
        }

        //returns the normalized axis score
        public float Evaluate (float x)
        {
            float val = x;

            if (m_type == CurveType.Linear)
                val = EvaluateLinear (x);
            else if (m_type == CurveType.Logistic)
                val = EvaluateLogistic (x);
            
            if (val > 1f)
                val = 1f;
            else if (val < 0f)
                val = 0f;

            return val;
        }

        private float EvaluateLinear(float x)
        {
            return m_m * ((float)Math.Pow(x - m_c, m_k)) + m_b;
        }

        private float EvaluateLogistic(float x)
        {
            float dividor = 1f + (float)Math.Pow(1000f * Math.E * m_m, -1f * x + m_c);
            float val = m_k * (1f / dividor) + m_b;

            //Logistic curces tend to approach zero but do not reach it within the scale
            if (val < 0.001f)
                val = 0f;

            return val;
        }
    }
}
