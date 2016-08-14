#pragma once

#include "QtnProperty/Core/Property.h"
#include "QtnProperty/Widget/Delegates/PropertyDelegate.h"

#include <set>
#include <memory>

namespace QtnPropertyExtension
{
	class PropertyConnector;
}

class QtnMultiPropertyDelegate;
class QtnMultiProperty : public QtnProperty
{
	Q_OBJECT

public:
	explicit QtnMultiProperty(const QMetaObject *propertyMetaObject, QObject *parent = nullptr);
	virtual ~QtnMultiProperty();

	void addProperty(QtnProperty *property, bool own = true);
	void resetValues();

	bool hasResettableValues() const;
	bool hasMultipleValues() const;

	static void Register();
	static QString getMultiValuePlaceholder();

private slots:
	void onPropertyValueAccept(const QtnProperty* property, QtnPropertyValuePtr valueToAccept, bool* accept);

	void onPropertyWillChange(const QtnPropertyBase* changedProperty,
							  const QtnPropertyBase* firedProperty,
							  QtnPropertyChangeReason reason, QtnPropertyValuePtr newValue);

	void onPropertyValueChanged(const QtnPropertyBase *changedProperty,
								const QtnPropertyBase *firedProperty,
								QtnPropertyChangeReason reason);

protected:
	virtual bool loadImpl(QDataStream &stream) override;
	virtual bool saveImpl(QDataStream &stream) const override;

	virtual bool fromStrImpl(const QString &str, bool edit) override;
	virtual bool toStrImpl(QString &str) const override;

	virtual bool fromVariantImpl(const QVariant& var, bool edit) override;
	virtual bool toVariantImpl(QVariant& var) const override;

private:
	void refreshValues();

	static QtnPropertyExtension::PropertyConnector
		*getPropertyConnector(QtnProperty *property);

	std::vector<QtnProperty *> properties;
	const QMetaObject *propertyMetaObject;

	bool calculateMultipleValues;
	bool multipleValues;

	friend class QtnMultiPropertyDelegate;
};

class QtnMultiPropertyDelegate
		: public QObject
		, public QtnPropertyDelegateTypedEx<QtnMultiProperty>
{
	Q_OBJECT
	Q_DISABLE_COPY(QtnMultiPropertyDelegate)

	typedef QtnPropertyDelegateTypedEx<QtnMultiProperty> Inherited;

public:
	QtnMultiPropertyDelegate(QtnMultiProperty& owner);
	virtual ~QtnMultiPropertyDelegate();

private slots:
	void onPropertyEdited();
	void onEditedPropertyDestroyed();
	void onEditorDestroyed();

protected:
	virtual bool propertyValueToStr(QString &strValue) const override;

	virtual void applyAttributesImpl(const QtnPropertyDelegateAttributes &attributes) override;
	virtual void drawValueImpl(QStylePainter &painter, const QRect &rect,
							   const QStyle::State &state, bool *needTooltip = nullptr) const override;
	virtual QString toolTipImpl() const override;
	virtual bool acceptKeyPressedForInplaceEditImpl(QKeyEvent *keyEvent) const override;
	virtual QWidget* createValueEditorImpl(QWidget *parent, const QRect &rect,
										   QtnInplaceInfo *inplaceInfo = nullptr) override;

private:	
	typedef std::unique_ptr<QtnPropertyDelegate> DelegatePtr;
	std::vector<DelegatePtr> superDelegates;

	QtnProperty *propertyToEdit;
};
