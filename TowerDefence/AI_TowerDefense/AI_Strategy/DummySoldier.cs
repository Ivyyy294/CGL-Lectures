using GameFramework;
namespace AI_Strategy
{
    /*
     * This class derives from Soldier and provides a new move method. Your assignment should
     * do the same - but with your own movement strategy.
     */
    public class DummySoldier : Soldier
    {
        bool advance = false;
        bool deployed = false;
        ActiveRegimentSettings m_activeRegimentSettings;
        /*
         * This move method is a mere copy of the base movement method.
         */
        public override void Move()
        {
            if (m_activeRegimentSettings == null)
                m_activeRegimentSettings = ActiveRegimentSettings.GetInstance(player.Name);

            if (deployed)
            {
                int x = posX;
                int y = posY;

                for (int i = speed; i > 0; i--)
                {
                    if (MoveTo(x, y + i)) return;
                    if (MoveTo(x + i, y + i)) return;
                    if (MoveTo(x - i, y + i)) return;
                    if (MoveTo(x + i, y)) return;
                    if (MoveTo(x - i, y)) return;
                    if (MoveTo(x, y - i)) return;
                    if (MoveTo(x - i, y - i)) return;
                    if (MoveTo(x + i, y - i)) return;
                }
            }
            else if (m_activeRegimentSettings.IsRegimentComplete())
                deployed = true;
            else if (posY < m_activeRegimentSettings.Depth -1)
                MoveTo (posX, posY + 1);
        }
    }
}
