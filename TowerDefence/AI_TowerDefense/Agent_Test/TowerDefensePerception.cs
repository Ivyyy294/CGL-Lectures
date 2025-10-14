using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Agent_Test
{
    public class TowerDefensePerception
    {
        public enum ActionTyp
        {
            DeployTowers,
            DeploySoldiers
        }

        public Player Player { get; set; }
        public ActionTyp CurrentActionTyp { get; set; }
    }
}
