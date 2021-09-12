#include "ui/UnkClass203.h"
#include "ui/UnkClass200.h"
#include "ui/controls/UIElement.h"
#include "engine/GraphicsHandler.h"
#include "graphics/DrawableSurface.h"
#include "io/MouseHandler.h"
#include "io/KeyboardHandler.h"

using knights_and_merchants::engine::GraphicsHandler;
using knights_and_merchants::graphics::DrawableSurface;
using knights_and_merchants::ui::controls::UIElement;
using knights_and_merchants::io::MouseHandler;
using knights_and_merchants::io::KeyboardHandler;

UnkClass203::UnkClass203(const Rect position, const char p4)
	: i12_containers { }, i24_controls { }, i44 { position }
{
	reset();
	i64 = p4;

	i36 = 1;
	i40 = true;
}

UnkClass203::~UnkClass203()
{
	destroyContainers();
	destroyControls();
	reset();
}

void UnkClass203::reset()
{
	i60 = 0;
	i8_base = nullptr;
	i4_parent = nullptr;
	i40 = false;
	i65 = 0;
}

void UnkClass203::destroyContainers()
{
	UnkClass203 * var4 = (getBase() != nullptr) ? getBase()->i878 : nullptr;

	if (i12_containers.startIterateBegin()) {
		do {
			UnkClass203 * element = i12_containers.unk002();

			if (var4 == element) {
				getBase()->i878 = nullptr;
				var4 = nullptr;
			}

			if (element != nullptr)
				element->vtable0(true);

		} while (i12_containers.moveNext());

		i12_containers.clear();
	}

	enableDrawAllChilds();
}

UnkClass200 * UnkClass203::getBase() const
{
	if (i8_base != nullptr)
		return i8_base;

	if (i4_parent != nullptr)
		return i4_parent->getBase();

	return nullptr;
}

void UnkClass203::destroyControls()
{
	UIElement * var4 = (getBase() != nullptr) ? getBase()->i874 : nullptr;

	if (i24_controls.startIterateBegin()) {
		do {
			auto element = i24_controls.unk002();

			if (var4 == element) {
				getBase()->i874 = nullptr;
				var4 = nullptr;
			}

			if (element != nullptr)
				element->vtable0(true);

		} while (i24_controls.moveNext());

		i24_controls.clear();
	}

	enableDrawAllChilds();
}





UnkClass202 * UnkClass203::getEntryI564(const int i) const
{
	return (i4_parent != nullptr) ? i4_parent->getEntryI564(i) : i8_base->getEntryI564(i);
}



UnkClass201 * UnkClass203::getEntryI4(const int i) const
{
	return (i4_parent != nullptr) ? i4_parent->getEntryI4(i) : i8_base->getEntryI4(i);
}







void UnkClass203::vtable0(const bool free)
{
	this->~UnkClass203();

	if (free)
		operator delete(this);
}

void UnkClass203::vtable4(DrawableSurface & surface)
{
	if (i40) {
		vtable12(surface);
		i40 = false;
	}

	if (i24_controls.startIterateBegin()) {
		do {
			UIElement * element = i24_controls.unk002();

			if ((element->i21_flags & 0x20) == 0x20) {
				element->vtable4(surface);

				if ((element->i21_flags & 0x80) == 0x80)
					element->i21_flags &= ~0x80;
				else
					element->i21_flags &= ~0x20;
			}
		} while (i24_controls.moveNext());
	}

	if (i12_containers.startIterateEnd()) {
		do {
			UnkClass203 * element = i12_containers.unk002();
			element->vtable4(surface);
		} while (i12_containers.movePrevious());
	}
}

void UnkClass203::vtable8(DrawableSurface & surface, const Rect & relativePosition)
{
	Rect position { relativePosition };

	position.move(i44.left, i44.top);
	surface.fillRectangle(position, getEntryI564(i64)->i4);
}

void UnkClass203::vtable12(DrawableSurface & surface)
{
	if ((i65 & 1) == 0)
		surface.fillRectangle(i44, getEntryI564(i64)->i4);	
}

void UnkClass203::vtable16()
{

}

bool UnkClass203::vtable20(short p0, int p4, int p8)
{
	return (i8_base == nullptr) ? i4_parent->vtable20(p0, p4, p8) : i8_base->vtable4(p0, p4, p8);
}





bool UnkClass203::handleEvents(MouseHandler * p0, KeyboardHandler * p4)
{
	UnkClass200 * base = getBase();

	auto isLeftButtonDown = p0->i64_isLeftButtonDown;

	auto var18 = p0->i0_position.x;
	auto var14 = p0->i0_position.y;
	auto var8 = 0;

	if (p4 != nullptr) {
		if (p4->isMenuDown())
			var8 |= 0x20000000;

		if (p4->isShiftDown())
			var8 |= 0x40000000;

		if (p4->isControlDown())
			var8 |= 0x80000000;
	}

	UIElement * var20 = base->i874;

	if (var20 == nullptr) {
		if (i24_controls.startIterateBegin()) {
			do {
				UIElement * var4 = i24_controls.unk002();

				if (var4 == nullptr)
					continue;

				if ((var4->i21_flags & 0x40) == 0x40 || (var4->i21_flags & 0x4) == 0x4) {
					if (var4->i26 != -1 && var4->vtable8(p0->i0_position))
						base->setI872(var4->i26);		
				} else {
				
					if (p4 != nullptr) {
						if ((var4->i21_flags & 0x100) == 0x100) {
							if (p4->isKeyDown(var4->i25))
								continue;

							if ((var4->i21_flags & 0x4000) == 0x4000) {
								var4->i21_flags &= ~0x118;
								continue;
							}

							var4->i21_flags &= ~0x118;
							enableDraw(var4);

							var8 = 0;

							if (p4->unkHaha())
								var8 |= 0x20000000;

							if (p4->unkHaha222())
								var8 |= 0x40000000;

							if (p4->unkHaha444())
								var8 |= 0x80000000;

							if (vtable20(var4->i23, 9, var8))
								return true;

							continue;
						} else {
							if (var4->i25 != 0 && p4->isKeyDown(var4->i25)) {
								var4->i21_flags |= 0x118;
								enableDraw(var4);

								if ((var4->i21_flags & 0x4000) == 0x4000) {
									vtable20(var4->i23, 9, var8);
								}

								return true;
							}
						}

					} 


					if (var4->vtable8(p0->i0_position)) {
						
						if (var4->i26 != -1)
							base->setI872(var4->i26);
						
						if ((var4->i21_flags & 2) == 0) {
							var4->i21_flags |= 2;
							enableDraw(var4);
						}

						if (isLeftButtonDown == 0) {
							if ((var4->i21_flags & 8) == 8) {
								var4->i21_flags &= ~8;
								enableDraw(var4);

								if (vtable20(var4->i23, 1, var8))
									return true;
							}
						} else {
						
							if ((var4->i21_flags & 0x1000) == 0) {
								if ((var4->i21_flags & 8) == 0) {
									var4->i21_flags |= 8;
									enableDraw(var4);
									p0->i64_isLeftButtonDown = 0;
									p0->i76 = 1;
									isLeftButtonDown = 0;
								}
							} else {
								enableDraw(var4);

								if ((var4->i21_flags & 0x800) == 0x800) {
									base->i874 = var4;
									var4->i21_flags |= 8;
									p0->i64_isLeftButtonDown = 0;
									p0->i76 = 1;
									isLeftButtonDown = 0;
									return true;
								}

								if (vtable20(var4->i23, 1, var8)) {
									p0->i64_isLeftButtonDown = 0;
									p0->i76 = 1;
									isLeftButtonDown = 0;
									return true;
								}
							}
						}

						if (p0->i68_isRightButtonDown == 0) {
							if ((var4->i21_flags & 0x10) == 0x10) {
								var4->i21_flags &= ~0x10;
								enableDraw(var4);

								if (vtable20(var4->i23, 3, var8))
									return true;
							}
						} else {
							if ((var4->i21_flags & 0x2000) == 0) {
								if ((var4->i21_flags & 0x10) == 0) {
									var4->i21_flags |= 0x10;
									enableDraw(var4);
								}
							} else {
								enableDraw(var4);

								if (vtable20(var4->i23, 3, var8))
									return true;
							}
						}

						if ((var4->i21_flags & 0x200) == 0x200) {
							var4->i21_flags |= 0x400;

							if (vtable20(var4->i23, 7, var8))
								return true;
						}

						if (p0->i72_isMiddleButtonDown == 0) {
							if ((var4->i21_flags & 0x8000) == 0x8000) {
								var4->i21_flags &= ~0x8000;
								enableDraw(var4);

								if (vtable20(var4->i23, 5, var8))
									return true;
							}
						} else {
							if ((var4->i21_flags & 0x2000) == 0) {
								if ((var4->i21_flags & 0x8000) == 0) {
									var4->i21_flags |= 0x8000;
									enableDraw(var4);
								}
							} else {
								enableDraw(var4);

								if (vtable20(var4->i23, 5, var8))
									return true;
							}
						}

						if ((var4->i21_flags & 0x200) == 0x200) {
							var4->i21_flags |= 0x400;

							if (vtable20(var4->i23, 7, var8))
								return true;
						}

					} else {
						if ((var4->i21_flags & 0x1A) != 0) {
							var4->i21_flags &= ~0x1A;
							enableDraw(var4);
						}

						if ((var4->i21_flags & 0x400) == 0x400) {
							var4->i21_flags &= ~0x400;

							if (vtable20(var4->i23, 8, var8))
								return true;
						}
					}
				}
			} while (i24_controls.moveNext());
		}
	} else {
		if (i24_controls.startIterateBegin()) {
			do {
				UIElement * var4 = i24_controls.unk002();
				if (var4 == var20) {
					if (isLeftButtonDown != 0) {
						var4->vtable12(var18, var14);
					} else {
						var4->i21_flags &= ~0x18;
						base->i874 = nullptr;

						vtable20(var4->i23, 1, var8);
					}

					return true;
				}
			} while (i24_controls.moveNext());
		}
	}

	vtable16();

	if (i12_containers.startIterateEnd()) {
		do
			if (i12_containers.unk002()->handleEvents(p0, p4))
				return true;
		while (i12_containers.movePrevious());
	}

	return false;
}





void UnkClass203::enableDrawAllChilds()
{
	if (i24_controls.startIterateBegin()) {
		do
			enableDraw(i24_controls.unk002());
		while (i24_controls.moveNext());
	}

	if (i12_containers.startIterateBegin()) {
		do
			i12_containers.unk002()->enableDrawAllChilds();
		while (i12_containers.moveNext());
	}

	i40 = true;
}


bool UnkClass203::addContainer(UnkClass203 * container)
{
	container->i4_parent = this;
	container->enableDrawAllChilds();

	return addContainerRaw(container);
}

bool UnkClass203::addContainerRaw(UnkClass203 * container)
{
	return i12_containers.add(0, container);
}





void UnkClass203::enableDraw(UIElement * control)
{
	control->i21_flags |= 0x20;

	if (i60 != 0)
		control->i21_flags |= 0x80;
}

bool UnkClass203::addControl(UIElement * control)
{
	control->i28 = this;

	enableDraw(control);
	return addControlRaw(control);
}

bool UnkClass203::addControlRaw(UIElement * control)
{
	return i24_controls.add(0, control);
}
