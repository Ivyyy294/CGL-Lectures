using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;

namespace AI_Strategy
{
    public class LaneRunnerStrategy : StrategyStateMachine
    {
        private ActiveRegimentSettings m_activeRegimentSettings;
        public LaneRunnerStrategy(Player player) : base(player)
        {
            m_activeRegimentSettings = ActiveRegimentSettings.AddInstance(player.Name);
            m_activeRegimentSettings.Width = 3;
            m_activeRegimentSettings.Depth = 3;
            m_activeRegimentSettings.StartIndex = 0;
            m_activeRegimentSettings.SoldierLane = player.EnemyLane;

            Push (new LaneRunnerBrain (this));
        }

        public override List<Soldier> SortedSoldierArray(List<Soldier> unsortedList)
        {
            return unsortedList.OrderByDescending(s => s.PosY).ToList();
        }

        public override List<Tower> SortedTowerArray(List<Tower> unsortedList)
        {
            return unsortedList;
        }
    }

    class LaneRunnerBrain : StrategyState
    {
        ActiveRegimentSettings m_activeRegimentSettings;
        public LaneRunnerBrain(StrategyStateMachine stateMachine) : base(stateMachine)
        {
            m_activeRegimentSettings = ActiveRegimentSettings.GetInstance(m_player.Name);
        }

        public override void Continue()
        {
            m_stateMachine.Push(new DeployRegimentState(m_stateMachine));
        }
        public override void DeploySoldiers()
        {
        }
        public override void DeployTowers()
        {
        }

        public override void Enter()
        {
            m_stateMachine.Push(new DeployRegimentState(m_stateMachine));
        }

        public override void Exit()
        {
        }
    }
}