#pragma once

class AnimUtils {
  public:
    template <typename T>
    static T* FindNotifyByClass(UAnimSequenceBase* animation) {
        if (animation == nullptr) {
            return nullptr;
        }
        for (auto notify_event : animation->Notifies) {
            auto anim_notify = Cast<T>(notify_event.Notify);
            if (anim_notify != nullptr) {
                return anim_notify;
            }
        }
        return nullptr;
    }
};