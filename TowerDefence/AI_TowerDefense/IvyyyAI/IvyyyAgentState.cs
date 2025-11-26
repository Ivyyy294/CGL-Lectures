using GameFramework;
using System;
using System.Collections.Generic;

namespace Agent_System
{
    public abstract class IvyyyAgentState <TPerception>
    {
        public delegate float ActionInputParameterMethod(object target);

        //Dictionary of available input paramters with their get method
        protected Dictionary<string, ActionInputParameterMethod> m_actionInputParameters = new();

        //Dictionary of available target lists
        protected Dictionary<string, List<object>> m_targetMap = new();

        public List<object> GetTargetList(string target)
        {
            if (m_targetMap.ContainsKey(target))
                return m_targetMap[target];
            else
            {
                DebugLogger.Log("Invalid target: " + target);
                return null;
            }
        }

        //Returns the normalized InputParameter for a target
        public float GetActionInputParameter(string parameterName, object target)
        {
            float val = 0f;

            if (m_actionInputParameters.ContainsKey(parameterName))
                val = m_actionInputParameters[parameterName](target);
            else
                DebugLogger.Log("Invalid ActionInputParameter: " + parameterName);

            //Clamp between 0 and 1
            val = Math.Max(0, val);
            val = Math.Min(1, val);

            return val;
        }

        public abstract void Update (TPerception perception);
    }
}
