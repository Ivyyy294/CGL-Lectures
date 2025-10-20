using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AI_Strategy
{
    public class TowerDefensePerception
    {
        public enum ActionTyp
        {
            TurnStart,
            TurnEnd,
            DeployTowers,
            DeploySoldiers
        }

        public Player Player { get; set; }
        public ActionTyp CurrentActionTyp { get; set; }
    }
}
