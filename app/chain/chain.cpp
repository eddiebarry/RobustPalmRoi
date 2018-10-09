/****************************************************************************\
 * Created on Mon Oct 08 2018
 * 
 * The MIT License (MIT)
 * Copyright (c) 2018 leosocy
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the ",Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED ",AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
\*****************************************************************************/

#include "chain/chain.h"


namespace rpr {

HandlerChain& HandlerChain::Join(std::unique_ptr<Handler> handler) {
  handlers_.emplace_back(std::move(handler));
  return *this;
}

Status HandlerChain::Process(const cv::Mat& orig, cv::Mat* res) {
  cv::Mat temp(orig.clone());
  Status status(Status::Ok());
  auto it = handlers_.begin();
  while (it != handlers_.end() && status.IsOk()) {
    status = (*it)->Handle(temp, &temp);
    it++;
  }
  *res = temp.clone();
  return status;
}

}   // namespace rpr
