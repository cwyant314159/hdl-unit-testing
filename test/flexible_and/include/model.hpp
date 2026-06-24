#ifndef MODEL_HPP
#define MODEL_HPP

template <class WidthT>
class Model
{
public:
    void SetInvertA(bool state) { m_invA = state; }
    void SetInvertB(bool state) { m_invB = state; }
    void SetInvertY(bool state) { m_invY = state; }

    WidthT Compute(WidthT a, WidthT b)
    {
        WidthT aActual = (m_invA) ? ~a : a;
        WidthT bActual = (m_invB) ? ~b : b;

        WidthT y = aActual & bActual;

        return (m_invY) ? ~y : y;
    }

private:
    bool m_invA{false};
    bool m_invB{false};
    bool m_invY{false};
};

#endif // MODEL_HPP