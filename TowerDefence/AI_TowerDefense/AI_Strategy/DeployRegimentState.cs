using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AI_Strategy
{
    public class DeployRegimentState : StrategyState
    {
        List<IvyyySoldier> m_regiment = new();

        ActiveRegimentSettings m_activeRegimentSettings;
        public DeployRegimentState(StrategyStateMachine stateMachine) : base(stateMachine)
        {
            m_activeRegimentSettings = ActiveRegimentSettings.GetInstance(m_player.Name);
        }

        public override void Continue()
        {
        }

        public override void DeploySoldiers()
        {
            if (m_player.Gold < m_activeRegimentSettings.Width * 2)
                return;

            for (int i = 0; i < m_activeRegimentSettings.Width; ++i)
            {
                int xPos = m_activeRegimentSettings.StartIndex + i;
                Player.SoldierPlacementResult result = m_player.TryBuySoldier<IvyyySoldier>(xPos);

                if (result == Player.SoldierPlacementResult.Success)
                {
                    Cell cell = m_player.EnemyLane.GetCellAt (xPos, 0);
                    IvyyySoldier soldier = (IvyyySoldier)cell.Unit;
                    m_regiment.Add (soldier);
                }
            }

            if (m_activeRegimentSettings.IsRegimentComplete())
                DeployRegiment();
        }

        public override void DeployTowers()
        {
        }

        public override void Enter()
        {
            DebugLogger.Log("#Player" + m_player.Name + " Gather Soldiers for Regiment!");

            EvaluateRegimentSize();
            SetRegimentStartIndex();
        }

        public override void Exit()
        {
        }

        private void DeployRegiment()
        {
            DebugLogger.Log("#Player" + m_player.Name + " Deploy Regiment!");

            foreach (var s in m_regiment)
            {
                if (s != null)
                    s.Deploy();
            }

            m_stateMachine.Pop();
        }

        private void EvaluateRegimentSize()
        {
            if (m_player.Gold >= 42)
                m_activeRegimentSettings.Width = 7;
            else if (m_player.Gold >= 36)
                m_activeRegimentSettings.Width = 6;
            else if (m_player.Gold >= 30)
                m_activeRegimentSettings.Width = 5;
            else if (m_player.Gold >= 24)
                m_activeRegimentSettings.Width = 4;
            else
                m_activeRegimentSettings.Width = 3;
        }

        private void SetRegimentStartIndex()
        {
            Random r = new Random();
            m_activeRegimentSettings.StartIndex = r.Next(0, 7 - m_activeRegimentSettings.Width);
        }
    }
}
