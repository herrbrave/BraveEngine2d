#include "Renderer.h"

void Renderer::render() {
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto ent : this->drawOrder) {
		EntityPtr entity = makeShared(ent);
		DrawableComponentPtr drawableComponent = makeShared(entity->getComponent<DrawableComponent>(DRAWABLE_COMPONENT_TYPE));
		PhysicsComponentPtr physicsComponent = makeShared(entity->getComponent<PhysicsComponent>(PHYSICS_COMPONENT_TYPE));
		DrawablePtr drawable = makeShared(drawableComponent->drawable);
		drawable->render(this->assetVendor, 0.0f, this->graphics->projection, this->graphics->view, physicsComponent->getPosition());
	}

	SDL_GL_SwapWindow(graphics->window.get());
}

void Renderer::registerEntity(WeakEntityPtr entity) {
	this->drawOrder.push_back(std::move(entity));
	std::sort(this->drawOrder.begin(), this->drawOrder.end(), [](WeakEntityPtr left, WeakEntityPtr right) {
		EntityPtr entityLeft = makeShared(left);
		DrawableComponentPtr l = makeShared(entityLeft->getComponent<DrawableComponent>(DRAWABLE_COMPONENT_TYPE));
		EntityPtr entityRigth = makeShared(right);
		DrawableComponentPtr r = makeShared(entityRigth->getComponent<DrawableComponent>(DRAWABLE_COMPONENT_TYPE));

		return l->depth < r->depth;
	});
}

void Renderer::deregisterEntity(const std::string id) {
	auto iter = std::find_if(this->drawOrder.begin(), this->drawOrder.end(), [&id](WeakEntityPtr ent) {
		EntityPtr entity = makeShared(ent);
		return entity->id == id;
	});
	this->drawOrder.erase(iter);
}