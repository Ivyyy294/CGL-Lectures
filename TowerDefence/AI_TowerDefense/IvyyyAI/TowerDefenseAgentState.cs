using Agent_System;
using GameFramework;

namespace AI_Strategy
{
    public class TowerDefenseAgentState : AgentState<TowerDefensePerception>
    {
        public int Gold { get; private set; }
        public int TowerCount { get; private set; }
        public int EnemyCount { get; private set; }
        public int RegimentCounter { get; set;}
        public Player Player { get; private set; }

        public TowerDefensePerception.ActionTyp ActionTyp {get; private set;}

        public override void Update(TowerDefensePerception perception)
        {
            Gold = perception.Player.Gold;
            TowerCount = perception.Player.HomeLane.TowerCount();
            EnemyCount = perception.Player.HomeLane.SoldierCount();
            ActionTyp = perception.CurrentActionTyp;
            Player = perception.Player;
        }
    }
}
