/*
add animator for a parameter

*/

#pragma once

#include "ofMain.h"
#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"


namespace msa {
	namespace controlfreak {

		class ParameterOscillator : public ParameterGroup {
		public:
			// oscillates a parameter
			ParameterOscillator(string name, ParameterGroup* parent = NULL, Parameter* targetParam = NULL)
				: ParameterGroup(name, parent) {

				this->targetParam = targetParam;

				addBool("enabled").set(false);
				//addNamedIndex("fn").setLabels(4, "sin", "cos", "tri", "saw", "square"); // TODO: implement
				addBool("ease").set(false);
				addFloat("period").setTooltip("period in seconds").setClamp(false).set(1);
				addFloat("phase").setTooltip("0 to 1, phase").set(0);
				addFloat("speed").setTooltip("speed multiplier").setClamp(false).set(1);
				addFloat("mmin").setClamp(false).set(-1);
				addFloat("mmax").setClamp(false).set(1);


				//bool enabled = true;
				//float freq = 0;     // oscilations per second
				//float phase = 0;    // phase offset
				//float speed = 1;    // speed (time mult)

				//bool ease = false;

				//// map to min, max
				//float mmin = -1;
				//float mmax = 1;
			}

			float radians(float time) const {
				return (time * get("speed").value()/ get("period").value() + get("phase").value()) * PI * 2;
			}

			float value(float time) const {
				if (get("enabled").value()) {
					float v = ofMap(sin(radians(time)), -1, 1, 0, 1);
					if (get("ease").value()) v = 3 * v * v - 2 * v * v * v;
					return ofLerp(get("mmin"), get("mmax"), v);
				}
				else {
					return targetParam != NULL ? targetParam->value() : 0;
				}
			}

			virtual void update() override {
				// TODO: how to manage time?
				if (targetParam && get("enabled").value()) {
					float time = Master::instance().getTime();
					float newValue = value(time);
					targetParam->set(newValue);
				}
			}

		protected:
			Parameter* targetParam;
		};
	}
}
