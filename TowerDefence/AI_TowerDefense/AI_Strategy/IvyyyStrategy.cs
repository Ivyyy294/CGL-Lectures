using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;

namespace AI_Strategy
{
    public class IvyyyStrategy : StrategyStateMachine
    {
        private ActiveRegimentSettings m_activeRegimentSettings;
        public IvyyyStrategy(Player player) : base(player)
        {
            m_activeRegimentSettings = ActiveRegimentSettings.AddInstance (player.Name);
            m_activeRegimentSettings.Width = 2;
            m_activeRegimentSettings.Depth = 3;
            m_activeRegimentSettings.StartIndex = 0;
            m_activeRegimentSettings.SoldierLane = player.EnemyLane;

            Push (new IvyyyBrain(this));
        }
        public override List<Soldier> SortedSoldierArray(List<Soldier> unsortedList)
        {
            return unsortedList.OrderByDescending(s => s.PosY).ToList();
        }

        public override List<Tower> SortedTowerArray(List<Tower> unsortedList)
        {
            return unsortedList.OrderByDescending(s => s.PosY).ToList();
        }
    }

    public class IvyyyBrain : StrategyState
    {
        ActiveRegimentSettings m_activeRegimentSettings;
        int regimentCounter = 0;
        public IvyyyBrain(StrategyStateMachine stateMachine) : base(stateMachine)
        {
            m_activeRegimentSettings = ActiveRegimentSettings.GetInstance (m_player.Name);
        }
        public override void Continue()
        {
            MakeDecision();
        }

        public override void DeploySoldiers()
        {
        }

        public override void DeployTowers()
        {
        }

        public override void Enter()
        {
            MakeDecision();
        }

        public override void Exit()
        {
        }

        private void MakeDecision()
        {
            if (regimentCounter <= 0)
            {
                regimentCounter = 1;
                m_stateMachine.Push(new DeployTowerState(m_stateMachine));
            }
            else
            {
                regimentCounter--;
                m_stateMachine.Push(new DeployRegimentState(m_stateMachine));
            }
        }
    }
}
