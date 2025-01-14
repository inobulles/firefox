/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

"use strict";

var utilityPid = undefined;
add_task(async () => {
  const utilityProcessTest = Cc[
    "@mozilla.org/utility-process-test;1"
  ].createInstance(Ci.nsIUtilityProcessTest);
  await utilityProcessTest
    .startProcess()
    .then(async pid => {
      utilityPid = pid;
      ok(true, "Could start Utility process: " + pid);
    })
    .catch(async () => {
      ok(false, "Cannot start Utility process?");
    });
});

add_task(async () => {
  SimpleTest.expectChildProcessCrash();

  const utilityProcessGone = TestUtils.topicObserved("ipc:utility-shutdown");

  info("Hard kill Utility Process");
  const ProcessTools = Cc["@mozilla.org/processtools-service;1"].getService(
    Ci.nsIProcessToolsService
  );
  ProcessTools.kill(utilityPid);

  info(`Waiting for utility process ${utilityPid} to go away.`);
  let [subject, data] = await utilityProcessGone;
  ok(
    subject instanceof Ci.nsIPropertyBag2,
    "Subject needs to be a nsIPropertyBag2 to clean up properly"
  );
  is(
    parseInt(data, 10),
    utilityPid,
    `Should match the crashed PID ${utilityPid} with ${data}`
  );
});
