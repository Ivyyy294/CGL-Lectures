using GameFramework;
using IvyyyAI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AI_Strategy
{
    public class ActiveRegimentSettings
    {
        private static Dictionary<string, ActiveRegimentSettings> m_instances = new Dictionary<string, ActiveRegimentSettings>();
        public PlayerLane SoldierLane {  get; set; }
        public int Width { get; set; }
        public int Depth { get; set; }
        public int SoldierCount => Width * Depth;
        public int StartIndex { get; set;}
        public List<IvyyySoldier> m_soldiers = new();

        //Public Methods
        public static ActiveRegimentSettings AddInstance (string key)
        {
            ActiveRegimentSettings newInstance = new ActiveRegimentSettings ();
            m_instances.Add (key, newInstance);
            return newInstance;
        }

        public static ActiveRegimentSettings GetInstance(string key)
        {
            if (m_instances.ContainsKey (key))
                return m_instances[key];
            else
                return null;
        }
        public bool IsRegimentComplete()
        {
            for (int i = 0; i < Depth; ++i)
            {
                if (!IsRowComplete(i))
                    return false;
            }

            return true;
        }

        public void Deploy()
        {
            foreach (var s in m_soldiers)
            {
                if (s != null)
                    s.Deploy();
            }

            m_soldiers.Clear();
        }

        //Private Methods
        public bool IsRowComplete(int row)
        {
            if (SoldierLane == null) 
                return false;

            for (int i = 0; i < Width; ++i)
            {
                if (SoldierLane.GetCellAt(StartIndex + i, row).Unit == null)
                    return false;
            }
            return true;
        }
    }
}
