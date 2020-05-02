#pragma once

#include <QTextDocument>
#include <rdapi/graph/functiongraph.h>
#include <rdapi/rdapi.h>
#include "../../hooks/idisassemblercommand.h"
#include "../../renderer/documentrenderer.h"
#include "../graphview/graphviewitem.h"

class DisassemblerBlockItem : public GraphViewItem
{
    Q_OBJECT

    public:
        explicit DisassemblerBlockItem(const RDFunctionBasicBlock* fbb, IDisassemblerCommand* command, RDGraphNode node, QWidget *parent = nullptr);
        virtual ~DisassemblerBlockItem();
        bool containsItem(const RDDocumentItem& item) const;

    public:
        int currentLine() const override;
        void render(QPainter* painter, size_t state) override;
        QSize size() const override;

    protected:
        void mouseDoubleClickEvent(QMouseEvent *e) override;
        void mousePressEvent(QMouseEvent *e) override;
        void mouseMoveEvent(QMouseEvent *e) override;
        void invalidate(bool notify = true) override;

    private:
        QSize documentSize() const;
        void setupDocument();

    signals:
        void followRequested(const QPointF& localpos);

    private:
        event_t m_cursorevent;
        std::unique_ptr<DocumentRenderer> m_renderer;
        const RDFunctionBasicBlock* m_basicblock;
        IDisassemblerCommand* m_command;
        QTextDocument m_textdocument;
        qreal m_charheight;
        QFont m_font;
};